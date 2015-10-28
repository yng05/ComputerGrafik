FILE(REMOVE_RECURSE
  "CMakeFiles/docs-doxygen"
  "html/index.hhp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/docs-doxygen.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
