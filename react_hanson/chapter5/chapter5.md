# ReactとJSX
```
・Reactコンポーネントの実体は、React要素および他のcomponentから構成されたツリーを返す関数
・実際の現場では、createElementではなく、関数呼び出しがネストしないようにJSXが用いられる。
・これはJSのコードの中に直接、XMLのようなタグベースの構文を記述するための言語拡張。
・これを使うことでネストしたcreateElementの呼び出しを記述する代わりに、最終的に描画したい要素を宣言的に記述可能となる。
```

# 5.1 JSXを使ってReact要素を記述する
```
・JSXではタグ名としてReactの要素名(type)を記述する。
・タグの属性としてプロパティ値を記述する。
・子要素であるchildrenは開始タグと終了タグの間に記述される。
```
- JSXの例
```jsx
<ul>
    <li>1 lb Salmon</li>
    <li>1 cup Pine Nuts</li>
    <li>2 cups Butter Lettuce</li>
    <li>1 Yellow Squash</li>
    <li>1/2 cup Olive Oil</li>
</ul>
```
- コンポーネントの記載を書き比べた例
```js
//React.createElement(IngredientsList, {list:[...]});
<IngredientsList List={[...]}/>
```
- 説明
```
・配列を波括弧で囲んでいる(Javascript式)
・JSX内にJS式を記述する際は、波括弧で囲む必要がある。
・コンポーネントをJSXで記述する際には、文字列リテラルやJS式をプロパティとして渡せる。
```

## 5.1.1 JSXとHTMLの違い
- コンポーネントタグ
```jsx
//JSXにはコンポーネントを記述できる
//コンポーネントの子要素にさらにコンポーネントの記載も可能

<IngredientsList>
    <Ingredient />
    <Ingredient />
    <Ingredient />
</IngredientsList>
```
- classNameプロパティ
```js
//予約語を避ける
<h1 className="fancy">Baked Salmon</h1>
```
- Javascript式
```js
//波括弧で囲まれた式は実行時に評価される
<h1>{title}</h1>
//文字列リテラル以外はすべてJS式なので真偽値等を記述する際にも囲む
<input type="checkbox" defaultChecked={false} />
```
- JS式の評価
```js
//文字列連結や関数呼び出しも可能
<h1>{"Hello" + title}</h1>
<h1>{title.toLowerCase().replace}</h1>
```
- JS式の中に、JSXを記述
```js
<ul>
    {props.ingredients.map((ingredient, i)=>(
        <li key="{i}">{ingredient}</li>
    ))}
</ul>
```
- ブラウザで実行するために
```
・すべてのJSXタグはブラウザで実行される前にcreateElementの呼び出しに変換される。
・そのためのツールがBabel
```

## 5.1.2 BabelによるJSXの変換
```
・JSXをサポートしているブラウザはない
・また最新のJSの構文はサポートされていない可能性がある
⇒Babelでコンパイル

Babel
    ・登場時は6to5という名前のコンパイルで、ES6をES5に変換していた。
    ・今では最新のECMAScriptの構文を実行するプラットフォームであり、JSXのような拡張構文をサポートされている
```

- CDNで配布されているBabelのライブラリを読み込み実行する。
```html
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        <title>React Examples</title>
    </head>

    <!--ReactとReactDOM-->
    <script
        src="https://unpkg.com/react@16.8.6/umd/react.development.js">
    </script>
    <script
        src="https://unpkg.com/react-dom@16.8.6/umd/react-dom.development.js">
    </script>

    <!--Babel-->
    <script
        src="https://unpkg.com/@babel/standalone/babel.min.js">
    </script>

    <script type="text/babel">
        //ここにJSXを記述
    </script>
</html>
```
- 説明
```
・<script>タグ内に書かれており、type="text/babel"が指定されているものは、実行前に自動的にBabelによりコンパイルされる
・変換のオーバーヘッドがあるので、ブラウザで簡単にテストしたいときにのみ使う
※ブラウザでBabelを実行すると、プロダクション環境の場合は事前コンパイルしてという警告が出る。
```

