# nvimチュートリアル

- 最新版のinstall方法
```
https://github.com/neovim/neovim/wiki/Installing-Neovim#appimage-universal-linux-package
```
- 実行
```
$ nvim
```

- settings.jsonにおける設定
```
・現状Remoteの方に書いている
```
- settings.json(中身)
```json
{
    "vscode-neovim.neovimExecutablePaths.linux": "/usr/bin/nvim",
    "vscode-neovim.useWSL": true,
    "vscode-neovim.neovimInitVimPaths.linux": "/home/toraneko/.config/nvim/init.vim",
    "extensions.experimental.affinity": {
        "asvetliakov.vscode-neovim": 1
    }
}
```

- nvimについて
```
~/.config/nvim/init.vim
    ・本家vimでいう~/.vimrc
    ・Neovim起動時に最初に読まれるスクリプト
    ・起動時に実行しても支障のないコマンドをinit.vimに書く(エディタの見た目や挙動設定等も)
    ・Vim scriptという言語で条件分岐などを使うこともできる
    ・プラグインを書いて読み込ませることもできる
    ・ファイルはインストール時に作成しておく
```

- 参考
```
https://qiita.com/KowerKoint/items/387074cf7022e2e0c8fe
```

- 方針
```
・vscodeのコードスニペットを試してから考える
```