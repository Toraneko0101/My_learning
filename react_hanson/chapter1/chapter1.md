# Reactの世界へようこそ

## 1.2 Reactの過去と未来

- 大まかな歴史
```
・13年にオープンソース化
・15年にNativeがリリース
・17年にFiberを導入
・19年にフックの導入
    statefullなReactコンポーネント間でステート管理のロジックを共有できる
```

- 破壊的な変更
```
最新の情報はReactの公式ブログ
https://react.dev/blog
をチェックする事
```

## 1.3 環境構築
- サンプルコード
```
https://github.com/oreilly-japan/learning-react-2e-ja
```

### 1.3.2 React Developer Tools
```
・ブラウザの拡張機能
・Reactを検知した場合、F12のComponentsタブで確認可能
・ローカルのHTMLファイルの場合は、詳細->ファイルのURLへのアクセスを許可
```

### 1.3.3 Node.jsのインストール
```
$ node -v
v20.9.0
```

### 1.3.3.1 npm
```
・Node.jsのパッケージ管理システム
・npmでプロジェクトを作成するとpackage.jsonファイルが生成
・npm installでpackage.jsonに記述された依存パッケージがinstallされる
```
- 自身のプロジェクトを新規作成する場合
```
$ npm init -y 
package.jsonが生成。(versionの範囲を記録している)
フォルダ名と同じ名前のプロジェクト名で初期化される
初期の依存パッケージリストは空
$ npm install <package-name>でinstall
$ npm remove <package-name>でuninstall

-gをつけるとグローバルインストール
    どこでも使えるようになる。
```

### 1.3.3.2 Yarn
```
Yarn
    ・Node.jsのパッケージ管理システム
    $ npm install -g yarn
    $ yarn add <package-name>
    $ yarn remove <package-name>

yarn.lock
    package.jsonみたいなもの
```
