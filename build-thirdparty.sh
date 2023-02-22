git submodule update --init --recursive
cd thirdparty/skia

python3 tools/git-sync-deps
bin/fetch-ninja

bin/gn gen out/Clang --args='cc="clang" cxx="clang++" is_official_build=true extra_cflags_cc=["-march=native"] skia_use_libwebp_encode=false skia_use_libwebp_decode=false'
ninja -C out/Clang

cd ../../