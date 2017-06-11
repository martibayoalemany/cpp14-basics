#!/usr/bin/env bash
git branch | head -1 | sed -e 's/\*//g' | sed -e "s/.*\/\(.*\)/\1/" | xargs -I{} -n1 git flow feature finish {}
