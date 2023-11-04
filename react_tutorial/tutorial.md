# 1.Reactインストール(WSL2上のUbuntu)
- 概要
```
npm
    ・Node Package Manager
    ・Javascript-app用の依存関係管理ツール
```
- node.jsのinstall
```
nvmのinstall
    $ curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/master/install.sh | bash

Node.jsの安定版をinstall
    nvm install --lts

現在のnode.jsのversion確認
    nvm list
```

- reactの一時的なinstall
```
npx create-react-app my-app
```

- Reactアプリの開始
```
npm start
```

- 注意点
```
.gitignoreにnode_modulesがあるか確認すること
```
# 2.最小構成のapp
- 注意点
```
・Reactアプリはcomponentで構成される
・componentは別のcomponentにnestできる
・Componentは大文字で始まる。htmlタグは小文字
```
```jsx
function MyButton(){
  return(
    <button>I'm a button</button>
  );
}

export default function MyApp(){
  return (
    <div>
      <h1>Welcome to my app</h1>
      <MyButton />
    </div>
  );
}

```

## styleの追加
```jsx
import './index.css';
<img className="avatar" />
```
```css
/* index.css */
.avatar {
    border-radius: 50%;
}
```

## dataの表示
```jsx
const user = {
  name: "Hedy Lamarr",
  imageUrl: 'https://i.imgur.com/yXOvdOSs.jpg',
  imageSize: 90,
}

export default function Profile(){
  return (
    <>
      <h1>{user.name}</h1>
      <img
        className="avatar"
        src={user.imageUrl}
        alt={"Photo of " + user.name}
        style={{
          width: user.imageSize,
          height: user.imageSize
        }}
      />
    </>
  );
}




```

- 依存関係のエラーが出たので対処
```
$ npm install --save-dev @babel/plugin-proposal-private-property-in-object

※Babelプラグインとして使われるので、開発中の依存関係に追加する
※プロジェクトの依存関係に追加したいpackageはnpm install。コンピュータ全体にインストールしたい場合はnpm install -g。開発時の依存関係としてインストールしたい場合は--save-dev

--save-dev
    ローカルインストール
    本番環境では使わない場合は、こちら
    このオプションを付けるとdevDependenciesに追加される
```

## 条件付きレンダー
```jsx
//通常版
let content;
if (isLoggedIn){
    content = <AdminPanel />;
}else{
    content = <LoginForm />;
}
return (
    <div>
        {content}
    </div>
);

//三項演算子
<div>
    {isLoggedIn ?(<AdminPanel />) : (<LoginFrom />)}
</div>

//elseが要らない場合
<div>
    {isLoggedIn && <AdminPanel />}
</div>
```

## リストのレンダー
```jsx
const products = [
  {title: "Cabbage", isFruit: false, id : 1},
  {title: "Garlic", isFruit: false, id : 2},
  {title: "Apple", isFruit: true, id :3},
];

export default function ShoppingList(){
  const listItems = products.map(product=>
      <li 
      key={product.id}
      style={{
        color: product.isFruit ? 'magenta' : 'darkgreen'
      }}
    >
      {product.title}
    </li>
  );

  return (
    <ul>{listItems}</ul>
  );
}

```
- 説明
```
・<></>はFragmentを宣言するための短縮記法である(昔は短縮記法だとkeyが指定できなかった時代があったらしい)

const listItems = products.map(product=>());
    ・アロー関数の後ろに丸括弧を使うと、returnを書かずに式が返る

・React16以降では必ずしも<div>や</div>で囲む必要はなくなった。
・コードを理解しやすくするためにラップするのはいいけども
・つまり複数の要素を直接リターン可能
⇒とりあえずは<>でreturnしたい

比較
const numbers = [1, 2, 3, 4, 5];

return (
  <ul>
    {numbers.map(number => (
      <li key={number}>{number}</li>
    ))}
  </ul>
);

const numbers = [1, 2, 3, 4, 5];

return (
  <ul>
    {numbers.map(number => {
      return <li key={number}>{number}</li>
    })}
  </ul>
);

Reactコンポーネント内のJSXが1つの式で囲まれている場合
その式が返り値となるためreturn文を省略可能
今回の場合、<li>単体なので省略可能。つまり()で囲む必要もない

```

## イベントに応答する
```jsx
function MyButton(){
  function handleClick(){
      alert("You clicked me!");
  }

  return(
      <button onClick={handleClick}>
          Click me
      </button>
  );
}

export default function MyApp(){
  return(
    <MyButton />
  );
}
```

## 画面の更新
```
・コンポーネントに情報を記憶させたいとき
・コンポーネントにstateを追加する
```
```jsx
//reactからuseStateをimportする
import { useState } from "react";

function MyButton(){
    //useStateからは現在のstate(count)と更新するためのsetCountが得られる。初期値はuseStateの中に入れる。stateを変更したいときはsetCount()を呼び出す
    const [count, setCount] = useState(0);

    function handleClick(){
        setCount(count+1);
    }

    return (
        <button onClick={handleClick}>
            Clicked {count} times
        </button>
    );
}

//reactは配列を直接returnすることを許している
function Mytest(){
    const Items = [
        <h1>neko</h1>,
        <h1>inu</h1>,
    ];
    return(
        Items
    );
}

//複数の場所でrenderした場合、独自のstateを持つ
//関数から呼んでいるので当然といえば当然だが
export default function MyApp(){
    return(
      <>
        <MyButton />
        <MyButton />
        <Mytest />
      </>
    );
}
```

## フックの使用
```
useで始まる関数
    ・Hook(フック)と呼ばれる
    ・useStateはReactが提供する組み込みのHook
    ・Hookを組み合わせて独自のHookを作成することも可能
    ・Hookはcomponentのtopレベルでだけ呼び出せる
```

## component間のデータ共有
```
・Mybutton間で、countの回数を共通化するには？
・その上位要素のMyAppにcountを持たせればいい
・状態を上に移動するということ

・波括弧で、渡される情報はpropsと呼ばれる
・以下ではonClickはMyApp内のhandleClick関数となっているので，その中のコードが実行される

```
- MyButtonにデータを渡す
```jsx
//reactからuseStateをimportする
import { useState } from "react";

function MyButton({count, onClick}){
    return (
        <button onClick={onClick}>
            Clicked {count} times
        </button>
    )
}

export default function MyApp(){
    const [count, setCount] = useState(0);

    function handleClick(){
        setCount(count + 1);
    }

    return (
        <>
            <h1>Counters that update separately</h1>
            <MyButton count={count} onClick={handleClick} />
            <MyButton count={count} onClick={handleClick} />
        </>
    );
}
```
## 三目並べを作成する

- App.js
```
・コンポーネントを作成する
・UIの部品を表す再利用可能なコード

export
    この関数をファイルの外部からアクセスできるようにする
default
    このコードを使用するほかのファイルにこの関数がmain関数であるということを伝える
単一のJSX要素
    複数の隣接するJSX要素はフラグメント<>で囲む
    同一行にない場合は、returnに()が必要
```
```jsx
export default function Square(){
    return <button className="square">x</button>
}
```
- styles.css
```css
/*className="square"*/
/* *とbodyの影響もうけている*/
  .square {
    background: #fff;
    border: 1px solid #999;
    float: left;
    font-size: 24px;
    font-weight: bold;
    line-height: 34px;
    height: 34px;
    margin-right: -1px;
    margin-top: -1px;
    padding: 0;
    text-align: center;
    width: 34px;
  }
```

- index.js
```
import {StrictMode} from 'react';
    React
import {createRoot} from "react-dom/client";
    Webブラウザとやり取りするためのReactライブラリ(ReactDOM)
import ".styles.css"
    component用のstyle
import App from "./App";
    App.jsで作成したcomponent
const root = createRoot(document.getElementById("root"))
    <div id="root"></div>に成果物を注入している

本番用のバンドルを作成するには
    npm run build or yarn build

```
```jsx
import {StrictMode} from 'react';
import {createRoot} from 'react-dom/client';
import "./styles.css";
import App from './App';

const root = createRoot(document.getElementById('root'));
root.render(
  <StrictMode>
    <App />
  </StrictMode>
);
```

- 複数要素を付け加えたApp.js
```jsx
function Square(){
    return <button className="square">1</button>
}

export default function Board(){
    return(
        <>
            <div className="board-row">
                <Square />
                <Square />
                <Square />
            </div>
            <div className="board-row">
                <Square />
                <Square />
                <Square />
            </div>
            <div className="board-row">
                <Square />
                <Square />
                <Square />
            </div>
        </>
    );
}
```
- 引数を渡したもの
```
・jsxからjsの記法に戻るためには波括弧が必要
・{value}という風に波括弧で囲むと、変数やプロパティの値が埋め込まれる。
```
```jsx
function Square({ value }){
    return <button className="square">{ value }</button>
}

export default function Board(){
    return(
        <>
            <div className="board-row">
                <Square value="1"/>
                <Square value="2"/>
                <Square value="3"/>
            </div>
            <div className="board-row">
                <Square value="4"/>
                <Square value="5"/>
                <Square value="6"/>
            </div>
            <div className="board-row">
                <Square value="7"/>
                <Square value="8"/>
                <Square value="9"/>
            </div>
        </>
    );
}
```

- 動的なcomponentの作成
```jsx
function Square({ value }){
    function handleClick(){
        console.log("clicked");
    }
    return (
        <button
            className="square"
            onClick={handleClick}
        >
            {value}
        </button>
    );
}

export default function Board(){
    return(
        <>
            <div className="board-row">
                <Square value="1"/>
                <Square value="2"/>
                <Square value="3"/>
            </div>
            <div className="board-row">
                <Square value="4"/>
                <Square value="5"/>
                <Square value="6"/>
            </div>
            <div className="board-row">
                <Square value="7"/>
                <Square value="8"/>
                <Square value="9"/>
            </div>
        </>
    );
}
```

- useStateで記憶させる
```jsx
import {useState} from "react";

function Square(){
    const [value, setValue] = useState(null);
    function handleClick(){
        setValue("X"); //valueの値がnull->xに更新される
    }
    return (
        <button
            className="square"
            onClick={handleClick}
        >
            {value}
        </button>
    );
}

export default function Board(){
    return(
        <>
            <div className="board-row">
                <Square />
                <Square />
                <Square />
            </div>
            <div className="board-row">
                <Square />
                <Square />
                <Square />
            </div>
            <div className="board-row">
                <Square />
                <Square />
                <Square />
            </div>
        </>
    );
}
```

- React Developer tools
```
・拡張機能
・開発者ツールにComponentsが追加される(Reactを使っている場合)
```

- stateのリフトアップ
```
・勝ち負けを知るには、Board側が9つのSquareコンポーネントそれぞれのstateを知る必要がある
・しかし、ゲームのStateをBoardで管理した方がいい

※複数のchildコンポーネントからデータを通信したい。
　あるいは2つのchild同士で通信したいと思ったら、親に共有のstateを持たせるべき
　親はprop経由でstateを子供に渡す
```