echo '================================================================='
echo '==                        Alunos                               =='
echo '================================================================='
cat ./alunos.txt
echo ''
echo ''
echo '================================================================='
echo '==     Em caso de duvidas/problemas leia o arquivo Readme.md   =='
echo '================================================================='
echo ''

make
echo "./bin/main < input.txt > result.txt"
./bin/main < input.txt > result.txt

echo ''
echo ''
echo '================================================================='
echo '==              Programa compilado e executado                 =='
echo '================================================================='