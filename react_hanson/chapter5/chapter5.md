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

# 5.2 レシピのコンポーネントをJSXで記述
```js
//data
const data = [
      {
        name: "Baked Salmon",
        ingredients: [
          { name: "Salmon", amount: 1, measurement: "l lb" },
          { name: "Pine Nuts", amount: 1, measurement: "cup" },
          { name: "Butter Lettuce", amount: 2, measurement: "cups" },
          { name: "Green Squash", amount: 1, measurement: "med" },
          { name: "Olive Oil", amount: 0.5, measurement: "cup" },
          { name: "Garlic", amount: 3, measurement: "cloves" },
        ],
        steps: [
          "Preheat the oven to 350 degrees.",
          "Spread the olive oil around a glass baking dish.",
          "Add the salmon, garlic, and pine nuts to the dish.",
          "Bake for 15 minutes.",
          "Add the yellow squash and put back in the oven for 30 mins.",
          "Remove from oven and let cool for 15 minutes. Add the lettuce and serve.",
        ],
      },
      {
        name: "Fish Tacos",
        ingredients: [
          { name: "Whitefish", amount: 1, measurement: "l lb" },
          { name: "Cheese", amount: 1, measurement: "cup" },
          { name: "Iceberg Lettuce", amount: 2, measurement: "cups" },
          { name: "Tomatoes", amount: 2, measurement: "large" },
          { name: "Tortillas", amount: 3, measurement: "med" },
        ],
        steps: [
          "Cook the fish on the grill until hot.",
          "Place the fish on the 3 tortillas.",
          "Top them with lettuce, tomatoes, and cheese",
        ],
      },
    ];
    //デストラクチャリングで受け取る
    const Recipe = ({ name, ingredients, steps }) => (
      //idをlower_caseに
      <section id={name.toLowerCase().replace(/ /g, "-")}>
        <h1>{name}</h1>
        <ul className="ingredients">
          {ingredients.map((ingredient, i) => (
            <li key={i}>{ingredient.name}</li>
          ))}
        </ul>
        <section className="instructions">
          <h2>Cooking Instructions</h2>
          {steps.map((step, i) => (
            <p key={i}>{step}</p>
          ))}
        </section>
      </section>
    );

    const Menu = ({ title, recipes }) => (
      <article>
        <header>
          <h1>{title}</h1>
        </header>
        <div className="recipes">
          {recipes.map((recipe, i) => (
            <Recipe key={i} {...recipe} />
          ))}
        </div>
      </article>
    );

    //recipesとtitleを要素として渡しながら描画
    ReactDOM.render(
      <Menu recipes={data} title="Delicious Recipes" />,
      document.getElementById("react-container")
    );
```
- recipesの中身はスプレッド記法でも置き換えられるが
```js
//全てのプロパティを渡しているので不要な値が渡る可能性がある
{
    props.recipes.map((recipe, i) =>
        <Recipe key={i} {...recipe} />
    );
}
```
- Components
```
・拡張機能を導入した後で、要素のツリーを表示して確認する。
```

### 5.2.1 Reactフラグメント
- 2つのコンポーネントを並列に描画したい場合
```js
function Cat({name}){
    return (
        <h1>The cat's name is {name}</h1>
        //ここに<p>等を付け足すとエラーとなる
    )
}

ReactDOM.render(
    <Cat name="Jungle" />,
    document.querySelector("root")
);
```
- 説明
```
・Reactでは2つ以上の要素をコンポーネントの戻り値として返せない
・大昔は<div>のようなラッパー要素が必要だった
・Reactフラグメントなら返せる
・実際の描画結果のDOMからはフラグメントは取り除かれる
```
- 改善案
```js
function Cat({name}){
    return(
        <React.Fragment>
            <h1>The cat's name is {name}</h1>
            <p>He's good</p>
        </React.Fragment>
    );
}
```
- 簡略記法
```js
function Cat({name}){
    return(
        <>
            <h1>The cat's name is {name}</h1>
            <p>He's good.</p>
        </>
    );
}
```

# 5.3 webpackを使ってビルド環境を構築する
```
Reactを実プロジェクトで採用するには、問題に対処する必要がある
・JSX, ES.nextの変換
・コンポーネント間の依存関係の管理
・画像やCSSの最適化

これらの問題を解決する手段の一つが[webpack]
・create-react-appで環境構築する際、裏で走っている仕組み
```

- webpack
```
webpack
・モジュールバンドラ

モジュールバンドラ
・異なる種類のファイルを単一のファイル(bundle)に結合するためのツール
・結合する理由は、モジュール化とネットワークパフォーマンス

モジュール化
・アプリケーションのソースコードをより小さな単位（モジュール）に分割する

ネットワークパフォーマンス
・ブラウザが依存fileをダウンロードする時間
・HTMLの<script>タグに依存fileを記述していると、それぞれのファイルが別々のHTMLリクエストによりDLされるので、ファイル数が増えるとリクエスト数による遅延が多くなる。
・依存fileを単一のファイルにまとめることで遅延を削減可能
```

- モジュールの結合以外のwebpackの機能
```
コード分割
    ・アプリケーションのコードを異なるバンドルに分割
    ・別名：ロールアップ、レイヤー
    ・異なるページやデバイスにおいて最低限必要なコードのみが含まれたバンドルをDLしたい時に有効

ミニファイ
    ・JSのファイルサイズを小さくするために、余計や空白や改行を取り除き、長い変数名を短くする

機能フラグ
    ・アプリケーションのコードの特定の部分を、環境変数の指定によりビルド時に有効化、無効化可能

Hot Module Replacement
    ソースコードの変更を監視し、リアルタイムに変更箇所をブラウザに反映する
```

- webpackによるビルドで得られる恩恵
```
モジュール化による利点
    ・モジュールをexportし、アプリケーションの他の箇所からモジュールをimportすること＝モジュールパターン
    ⇒チームでの共同開発が容易

合成による利点
    ・モジュールはシンプルであるほど再利用性が高い
    ・他のモジュールとの合成が容易になる
    ・小さなコンポーネントは差し替えが容易

ロード時間
    ・依存fileとすべてのモジュールを単一のbundleにパッケージングすることでappをロードする時間が減る
    ⇒1回のHTTPリクエストでappを取得できるため
    ⇒ミニファイすることで、bundle自体のサイズが減るため

一貫性
    ・webpackをbabel等と併用することで、最新のJS構文を使える
    ・そのためブラウザごとの実装の違いに時間を捕らわれることがなくなる
```

## 5.3.1 プロジェクトの作成
```
1. プロジェクトを作成する
2. レシピのアプリケーションを複数のコンポーネントに分割し、異なるファイルに記述
3. appをwebpackでビルドできるようにする

※普段はcreate-react-appでReactのプロジェクトを自動生成すればいい
　コマンド実行により、設定済みのファイルが生成される
```

1. プロジェクトフォルダの構成
```
$ npm init -y //package.jsonの生成(-yでデフォルト値)
$ npm install react react-dom serve //react, react-domのinstall

```

- 以下のようなディレクトリ構造にする
```
$ tree -I node_modules
.
├── data
│   └── recipes.json
├── index.html
├── package-lock.json
├── package.json
└── src
    ├── components
    │   ├── Ingredient.js
    │   ├── IngredientsList.js
    │   ├── Instructions.js
    │   ├── Menu.css
    │   ├── Menu.js
    │   └── Recipe.js
    └── index.js
```
2. モジュール分割
- index.js
```js
import React from "react";
import {render} from "react-dom";
import data from "../data/recipes.json"; //dataはここに格納
import Menu from "./components/Menu";

//Menuコンポーネントは以下で定義
//recipesにはデータ全部を渡している
render(
    <Menu recipes={data} />, 
    document.querySelector("root")
);
```
- Menu.js
```js
import React from "react";
import Recipe from "./Recipe";

function Menu({recipes}){
    return(
        <article>
            <header>
                <h1>Delicious Recipes</h1>
            </header>
            <div className = "recipes">
                {recipes.map((recipe, i)=>(
                    <Recipe key={i} {...recipe} />
                ))}
            </div>
        </article>
    )
};

export default Menu;
```
- Recipe.js
```js
import React from "react";
import IngredientsList from "./IngredientsList";
import Instructions from "./Instructions";

function Recipe({name, ingredients, steps}){
    return(
        <section id={name.toLowerCase().replace(/ /g, "-")}>
            <h1>{name}</h1>
            <IngredientsList list={ingredients} />
            <Instructions title="Cooking Instructions" steps={steps} />
        </section>
    );
}

export default Recipe;
```
- Instructions.js
```js
import React from "react";

/**
 * 名前と、手順を受け取る
 */
export default function Instructions({title, steps}){
    return(
        <section className="instructions">
            <h2>{title}</h2>
           {/* 1行なのでreturnを省いている */}
            {steps.map((s,i)=>(
                <p key={i}>{s}</p>
            ))}
        </section>
    );
}
```
- IngredientsList.js
```js
import React from "react";
import Ingredient from "./Ingredient";

{/*ingredientsがlistとして渡される */}
export default function IngredientsList({list}){
    return(
        <ul className = "ingredients">
            {/* スプレッド構文で、ingredientの全プロパティを渡している*/}
            {/*Ingredientに値を渡す */}
            {list.map((ingredient, i)=>(
                <Ingredient key={i} {...ingredient} />
            ))}
        </ul>
    );
}
```
- Ingredient.js
```js
import React from "react";

/**
 * デストラクチャリングを用いて、propsオブジェクトから
 * amount, measurement, nameのデータを抽出
 */
export default function Ingredient({amount, measurement, name}){
    return(
        <li>
            {amount} {measurement} {name}
        </li>
    );
}
```
- 説明
```
・これらをwebpackでビルドする
⇒ファイルに分割したモジュールを単一のファイルにできる

・モジュールの分割はチームのためであり、ファイルが分かたれている方が効率があがる。
・単一のファイルにビルドするのは、ブラウザで効率よくロードするため
```

3. ビルド環境の構築
```
$ npm install --save-dev webpack webpack-cli

・dev-dependenciesに追加する
```
- 設定ファイルを記述する
```
・アプリを単一のファイルに結合するには、webpackに対して結合手順を教える必要がある
・プロジェクトごとに設定ファイルを記述する(<=4.00なら設定ファイルナシでも可能だが、動作をカスタマイズしたい場合は必要)
・設定ファイルはwebpack.config.jsでプロジェクトのrootに配置されている必要がある

・webpackはファイルを読み、importを見つけた場合、対象のモジュールをファイルシステムから呼び出してバンドルに追加する
・ファイルの読出しは連鎖的に行われれ、importのツリーをたどることで、必要なすべてのモジュールがバンドルに追加される
・その過程で、依存モジュールのグラフが形成される
・React等の外部ライブラリや画像なども依存モジュールとして扱われれる。
・成果物がバンドルファイル

webpack.config.js
    ・単一のオブジェクトをexportするNode.jsのモジュール
    ・webpackのふるまいを規定するためのparamが格納
```
- webpack.config.jsを直下に追加
```js
var path =  require("path");

/**
 * entryファイルを指定:ここを起点にimportをparseする
 * output: 出力先（依存モジュールを単一のファイルに結合したもの）を指定 ./dist/assets/bundle.js
 */
module.exports = {
    entry: "./src/index.js",
    output: {
        path: path.join(__dirname, "dist", "assets"),
        filename: "bundle.js"
    }
};
```
- JSXをコンパイルするために、babelをinstallする
```
$ npm install babel-loader @babel/core --save-dev
```
- webpack.config.jsに追記
```js
var path =  require("path");

/**
 * entryファイルを指定:ここを起点にimportをparseする
 * output: 出力先を指定 ./dist/assets/bundle.js
 */
module.exports = {
    entry: "./src/index.js",
    output: {
        path: path.join(__dirname, "dist", "assets"),
        filename: "bundle.js"
    },

    module:{
        rules: [{test:/\.js$/, exclude: /node_modules/, loader: "babel-loader"}]
    }
};
```
- 説明
```
・moduleについてはmoduleフィールドに記載する
・rulesフィールドは配列で使用するモジュールの設定値を記述する
・今回はbabel-loaderの設定値のみを記述しチエル
・testには処理対象のファイルを正規表現で指定
⇒*.jsのファイルはすべて、babek-loaderに処理されるように
・excludeには除外したいファイルを指定
```
- Babelのプリセットを指定する
```
・Babelのふるまいを変えるための設定
⇒Babelの設定ファイルに記述する
⇒Babelの設定ファイルは.babelrc
```
- プリセットをinstall
```
$ npm install @babel/preset-env @babel/preset-react --save-dev
```
- プリセットを.babelrcに記述
```json
{
    "presets": ["@babel/preset-env","@babel/preset-react"]
}
```

- ビルドを実行してみる
```
$ npx webpack --mode development

・ここではwebpackは静的に実行されるので、アプリがサーバにデプロイされる前にあらかじめバンドルがビルドされている必要がある
・出力先のdistはgitignoreに追加した
```

- 以降のビルドを楽にするために
```js
//package.jsonのscriptsセクションに、
//本番用と記載
"scripts": {
  "build": "webpack --mode production"
},

// $ npm run buildとすることでwebpackの面倒な引数を指定する必要がなくなる
```

## 5.3.2 バンドルファイルのロード
- ブラウザにロードする
```
・通常distフォルダには、webサーバで配信したファイルが置かれる
・今回はdist直下にindex.htmlを作成し記述していく
```
- ロードするファイル
```html
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>React Recipes App</title>
    </head>
    <body>
        <div id="root"></div>
        <!--1回のloadで済む-->
        <script src="assets/bundle.js"></script>
    </body>
</html>
```

## 5.3.3 ソースマップ
```
・単一のファイルに依存モジュールをビルドすることのデメリットがデバッグが困難になること
・これを解決するのがソースマップ
・ソースマップはbandleのような変換後のコードと元のソースコードとの間で行番号をマッピングする
・Sourcesタブの中で表示する
⇒ブレークポイントを設定したりすることや、スコープ内の変数の値を参照したり、Watchで変数を登録して監視することも可能
```
- webpack.config.js
```js
    devtool : "inline-source-map"
```

## 5.3.4 Create React App
```
・コマンドラインのツールで、実行することでwebpack, Babel, ESLint等の設定ファイルを自動生成する
```
- 使い方
```
//npxは実行ツール。installされていないpackageでも自動的に探してinstallし、実行し、実行後に削除する
$ npx create-react-app my-project
```

- 自動生成されたもの
```
・ルートにはsrcがあり、App.jsが自動生成されている
・react, react-dom, react-scriptsがinstallされている(package.jsonに記載済み)

react-scripts
    ・Facebookにより提供されている
    。Babel, ESLint, webpack等が含まれている

```
- 起動
```
npm start
    ブラウザが起動してアプリが表示される
npm test
    ユニットテストを実行
    プロジェクトフォルダ内のすべてのテストを対話モードで実行

npm run build (yarn build)
    buildフォルダ配下にミニファイされたbundleファイルが出力 
```

- create-next-app
```
・next.jsが提供している、コマンド一つでwebアプリを実装してくれる機能
$ npx create-next-app
$ npm run dev
```