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

echo -n "primera prueba" > input
echo -n "input: "
cat input
echo "\\EOF"

echo -e "\ngenerando resultado esperado..."
cat input | grep -o . | sort | tr -d "\n" > expected
echo -n "resultado esperado: "
cat expected
echo "\\EOF"

echo -e "\ncorriendo prueba..."
./tp input > actual
#echo -n " aabeeimpprrru" > actual
echo -n "resultado obtenido: "
cat actual
echo "\\EOF"

echo -e "\ncorriendo comparación: diff actual expected\n"
diff actual expected
if [ ! $? -eq 0 ]
	then
	echo "prueba fallida..."
	exit_value=1
	else
	echo "prueba exitosa..."
fi

exit $exit_value
