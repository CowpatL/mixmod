#./cp_cmake.sh 32 or ./cp_cmake.sh 64

#test le nombre d'argument passé
if  test $# -ne 1
then
	echo 'il manque un argument (32 ou 64) decrivant l architecture'
  else


  # LIB (64 or 32 bits)
  cp -R ../../../../../UTIL/LIB/LINUX/LIB$1/thirdparty/lib*.so* ../../LIB/thirdparty/
 # cp -R ../../../../../UTIL/LIB/LINUX/LIB$1/mixmod/libMixmod.so* ../../LIB/mixmod
  #cp -R ../../../../../UTIL/LIB/LINUX/LIB$1/mixmod/libNewmat.so* ../../LIB/mixmod
fi
