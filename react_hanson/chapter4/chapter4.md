# Reactの基本
```
・Reactを使う時、JSXを併用する
JSX
    HTMLに似たタグをjsの中に直接記述できる拡張構文

本章で学ぶこと
    カスタムコンポーネントを合成する手法
```

# 4.1 使用するライブラリ
```
React + ReactDOM
    ・ブラウザでReactを動作させるうえで、最低限必要になる2つのライブラリ

React
    ・ビューを構築するためのライブラリ

ReactDOM
    ・Reactで構築されたビューをブラウザで描画するためのライブラリ

両方のライブラリについて
    ・unpkg.comが提供するCDNからDL可能
```

# 4.2 React要素
- HTMLについて
```
・ブラウザはHTMLに書かれてある通りにDOMを構築する
・HTMLに記述されている個々のタグが、ブラウザによりDOM要素に変換され描画される形
・HTMLの各要素間の関係は家系図のようなもので、親要素と子要素からなる。
・初期のWEBサイトは独立したHTMLページにより構成されており、ユーザがページ遷移するために、ブラウザは異なるHTMLドキュメントをロードしていた。
```
- AJAXの登場
```
AJAX: Asynchronous Javascript and XML
    ・AJAXの登場により、SPA(Single Page Application)が主流となった。

SPA
    ・画面遷移の際にドキュメント全体をロードするのではなく、ドキュメントの一部のみをロードしてページを部分的に更新するアプリケーション。
    ・HTMLドキュメントは初回に1度だけロードされ、以降は画面遷移の度に部分的に更新される。
    ・つまり、ユーザはページを遷移しているかのように見えて、実は同じページにずっととどまっており、ユーザがアプリを操作するたびにページの一部が破棄され、差し替えられる。

    ・そのようなページの更新をJSで行うため、ブラウザはDOM APIを提供する。document.createElementやdocument.appendChildなどの関数はすべてDOM API
```

- React と DOMAPI
```
・ReactはDOM APIの呼び出しを一手に引き受ける
・開発者はReactに対して指示書を渡す
・Reactは指示書に従ってUIを構築、描画し、複数の描画要求を調整する
・ReactのコンポーネントはReact要素から構成されている
```

- React要素を作成するコード
```js
React.createElement("h1", {id : "recipe-0"}, "Baked Salmon");
```
- 説明
```
最初の引数: <h1>要素
2番目の引数: 要素のプロパティ (id="recipe-0")
3番目の引数: 子要素(この場合はテキスト値)

上記の要素をReactは以下のようなDOM要素として返す
    <h1 id="recipe-0">Baked Salmon</h1>
    ・React要素の実体は、どのようにDOM要素を構築するかが記述されたJSオブジェクト
```
- 上記の<h1>のReact要素をコンソールに出力した場合
```json
{
    $$typeof: Symbol(React.element),
    "type" : "h1",
    "key" : null,
    "ref" : null,
    "props" : {id: "recipe-0", children: "Baked Salmon"},
    "_owner" : null,
    "_store" : {}
}
```
- 説明
```

```