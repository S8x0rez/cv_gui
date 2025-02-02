# Windows　

MSYS2をインストール

コンパイラ，GTK4を導入（[サイト](https://www.gtk.org/docs/installations/windows)を参考に）
```
pacman -S mingw-w64-x86_64-w64-gtk4
pacman -S mingw-w64-x86_64-w64-toolchain base-devel
```

CVとcv_guiをダウンロード(別々のディレクトリに配置するときはMakefileを適宜修正)
