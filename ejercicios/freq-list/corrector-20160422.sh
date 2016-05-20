#!/bin/bash

cp /srv/jarvis/workspace/makefile .

echo "compilando..."

make 2>&1
if [ ! $? -eq 0 ]
then
		echo "entrega fallida: error de compilacion"
		exit 1
fi

echo "compilacion exitosa"

echo -e "\n-------------------\n"

exit_value=0

echo "corriendo prueba..."

echo -n "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum" > input
echo -n "input: "
cat input
echo "\\EOF"

echo -e "\ngenerando resultado esperado..."
grep -o -P '[^ \t\n,.?]+' input | sort | uniq -c | awk '{print $2","$1}' > expected
echo -n "resultado esperado: "
cat expected
echo "\\EOF"

echo -e "\ncorriendo prueba..."
./tp input > actual
echo -n "resultado obtenido: "
cat actual
echo "\\EOF"
echo "ordenando salida de ejecucion real..."
cat actual | sort > sorted
echo -e "\ncorriendo comparación: diff sorted expected\n"
diff sorted expected
if [ ! $? -eq 0 ]
	then
	echo "prueba fallida..."
	exit_value=1
	else
	echo "prueba exitosa..."
fi

exit $exit_value
