echo ".cpp:"
cat `find ./src -name *.cpp` | wc -l
echo ".h:"
cat `find ./src -name *.h ` | wc -l
echo "shaders:"
cat `find ./data/shaders` 2> /dev/null | wc -l
echo "cfg:"
cat `find ./data -name *.json` | wc -l
