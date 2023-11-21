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
・_owner, __store, $$typeofはReactで内部的に使用されるフィールド
・key, ref : 後ほど
・type: Reactに対して何の要素を作成するか
・prpos: 要素に設定するデータと、子要素
・⇒childernにネストした子要素を記述する

※実際に。React.createElementの戻り値のobjectの中身をリテラルとして記述することはない。JSX等がよくつかわれる。
```

## 4.2.1 ReactDOMで要素をブラウザに描画
```js
const dish = React.createElement("h1", null, "Baked Salmon");

ReactDOM.render(dish, document.getElementById("root"));
```
```html
<body>
    <div id="root">
        <h1>Baked Salmon</h1>
    </div>
</body>
```
- 説明
```
・ReactDOM.renderを用いてReact要素とその子要素を描画している
・renderの第1要素にReact要素を、第2引数に要素を追加するルートノードを記載する。
・ver16以降なら、複数の要素をrenderに渡すことが可能
```
- 複数要素の描画
```js
const dish = React.createElement("h1", null, "Baked");
const dessert = React.createElemenet("h2", null, "Pie");
ReactDOM.render([dish, dessert], document.querySelector("#root"));
```

## 4.2.2 子要素(props.children)
```
・子要素はprops.childrenに格納される
・他のReact要素を子要素として指定することも可能。
・ネストした要素のツリーを構築する。
```
- 例
```js
React.createElement(
    "ul",
    null,//property
    React.createElement("li", null, "parsley"),
    React.createElement("li", null, "and"),
    React.createElement("li", null, "sage"),
    React.createElement("li", null, "and"),
    React.createElement("li", null, "thyme")
);

console.log(list);

//createElementの3番目以降の引数はすべて子要素とみなされる
//任意の数の子要素を引数として渡すことが可能。

```

- 少し大きなReactの要素を記述すzる。
```js
React.createElement(
    "section",
    {id : "baked-samon"},
    React.createElement("h1", null, "Baked Salmon"),
    React.createElement(
        "ul",
        {className: "ingredients"},
        React.createElement("li", null, "2, lb salmon"),
        React.createElement("li", null, "fresh rosemary"),
        React.createElement("li", null, "small lemons")
    ),
    React createElement(
        "section",
        {className: "instructions"},
        React.createElement("h2", null, "Cooking Instructions"),
        React.createElement("p", null, "Samon boil"),
        React.createElement("p", null, "Remove from oven")
    ),
);
```
- 説明
```
・ReactではclassはclassNameとなる。classが予約語なので
```

## 4.2.3 配列から子要素を作成する
