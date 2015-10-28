FILE(REMOVE_RECURSE
  "CMakeFiles/generate"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/generate.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
