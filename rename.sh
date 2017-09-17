#!/bin/bash
# 使い方
# 1. rime test を実行してrime-outディレクトリを作成する。
# 2. % cp rime-out/tests/*.in rime-out/tests/*.diff [できたファイルを入れるディレクトリ]
# 3. % cd [できたファイルを入れるディレクトリ]
# 4. このスクリプトを実行
#    % ./rename.sh
# 以上です。
# 

n=0
for f in `ls *.in`
do
  for g in `ls *.diff`
  do
    fn=`echo $f | sed -e 's/\.in//'`
    gn=`echo $g | sed -e 's/\.diff//'`
    if [ "$fn" = "$gn" ]
    then
      n=$((n+1))
      echo mv $f in$n.txt
      echo mv $g out$n.txt
      mv $f in$n.txt
      mv $g out$n.txt
    fi
  done
done

echo $n > case.txt
