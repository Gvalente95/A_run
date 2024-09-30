find . -name "*.sh" | sed 's/\(.*\)\.sh/\1/' | sed '/^$/d' | sed 's|^\./||'
