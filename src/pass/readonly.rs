//! Discharge provisional evaluation checks against selected native definitions.
use std::{
    collections::{HashMap, HashSet},
    rc::Rc,
};

use crate::{
    diag::{Diagnostic, DiagnosticLevel, Diagnostics},
    ir::{DeclT, SourceInfo, TranslationUnit},
};

use super::linkage::UnitSymbols;

#[derive(Default)]
pub struct Facts {
    pub definitions: HashMap<Rc<str>, Definition>,
    pub requirements: Vec<(Rc<str>, Rc<SourceInfo>)>,
    pub forbidden: HashSet<Rc<str>>,
}

pub struct Definition {
    pub supported: bool,
    pub dependencies: Vec<Rc<str>>,
}

fn supported(
    name: &Rc<str>,
    definitions: &HashMap<Rc<str>, Vec<&Definition>>,
    visiting: &mut HashSet<Rc<str>>,
    done: &mut HashMap<Rc<str>, bool>,
) -> bool {
    if let Some(result) = done.get(name) {
        return *result;
    }
    if !visiting.insert(name.clone()) {
        return false;
    }
    let result = definitions.get(name).is_some_and(|bodies| {
        bodies.iter().all(|body| {
            body.supported
                && body
                    .dependencies
                    .iter()
                    .all(|dependency| supported(dependency, definitions, visiting, done))
        })
    });
    visiting.remove(name);
    done.insert(name.clone(), result);
    result
}

pub fn check(units: &[(TranslationUnit, UnitSymbols)], diags: &mut Diagnostics) {
    let mut definitions: HashMap<Rc<str>, Vec<&Definition>> = HashMap::new();
    for (tu, symbols) in units {
        // A raw AST summary cannot justify a missing or replaced native body.
        let emitted: HashSet<_> = tu
            .decls
            .iter()
            .filter_map(|decl| {
                if let DeclT::FnDefn(body) = &decl.val {
                    Some(body.decl.name.val.clone())
                } else {
                    None
                }
            })
            .collect();
        for (name, body) in &symbols.readonly.definitions {
            if emitted.contains(name) {
                definitions.entry(name.clone()).or_default().push(body);
            }
        }
        for (_, symbols) in units {
            for name in &symbols.readonly.forbidden {
                definitions.remove(name);
            }
        }
    }
    let mut visiting = HashSet::new();
    let mut done = HashMap::new();
    let mut reported = HashSet::new();
    for (_, symbols) in units {
        for (name, loc) in &symbols.readonly.requirements {
            if !supported(name, &definitions, &mut visiting, &mut done) {
                let location = loc.location().clone();
                if !reported.insert((name.clone(), format!("{location:?}"))) {
                    continue;
                }
                diags.report(Diagnostic {
                    loc: location,
                    level: DiagnosticLevel::Error,
                    msg: format!(
                        "unsupported ignored variadic argument: {name} requires a selected, supported read-only native definition and acyclic definition-backed callees"
                    ),
                });
            }
        }
    }
}
