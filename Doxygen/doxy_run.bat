SET GRAPHVIZ_DOT="C:\Program Files\Graphviz\bin\dot.exe"
SET DOXYGEN_EXE="C:\Program Files\doxygen\bin\doxygen.exe"
SET SOURCE_DIR=C:\hw3
SET DOC_IMG_PATH_UML=..\doxygen\Resources
SET DOC_IMG_PATH=../doxygen/Resources
:: SET STRIP_PATH="C:xx"
java -jar "plantuml.jar" -v -o "%DOC_IMG_PATH_UML%" "%SOURCE_DIR%/**.(c|cpp|doc|h)"
doxygen Doxyfile
pause
