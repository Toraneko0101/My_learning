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
```jsx
import {useState} from "react";

function Square({value}){
    return <button className="square">{value}</button>;
}

export default function Board(){
    //それぞれが配列になる
    const [squares, setSquares] = useState(Array(9).fill(null));
    return(
        <>
            <div className="board-row">
                <Square value={squares[0]} />
                <Square value={squares[1]} />
                <Square value={squares[2]} />
            </div>
            <div className="board-row">
                <Square value={squares[3]} />
                <Square value={squares[4]} />
                <Square value={squares[5]} />
            </div>
            <div className="board-row">
                <Square value={squares[6]} />
                <Square value={squares[7]} />
                <Square value={squares[8]} />
            </div>
        </>
    );
}
```
- Clickされたときに起こることを定義する
```
・SquareからBoardのStateを更新する手段が必要
・StateはComponentにprivateなので直接変更はできない
・BoardからSquareに関数を渡して、Click時に呼び出せばいい
```

- 以下がうまくいかない理由
```jsx
Square value={squares[0]} onSquareClick={handleClick(0)} />
```
```
・Boardコンポーネントのレンダー時にhandleClick(0)が発動するから
・以前はhandleClickなので問題なかった
・ユーザがクリックするまでhandleClickを呼び出さないようにするには?

解決策1
    handleClick(0)を呼び出す関数を作成
解決策2
    onSquareClick={() => handleClick(0)} 
    マス目がクリックされると、=>の右辺が実行される
```

- 任意のマス目をClickしてXを描画する
```jsx
import {useState} from "react";

function Square({value, onSquareClick}){
    return <button className="square" onClick={onSquareClick}>
        {value}
    </button>;
}

export default function Board(){
    const [squares, setSquares] = useState(Array(9).fill(null));
    //squaresにアクセスできるのはclosureをsupportしているため
    //内側の関数は外側の関数で定義されている変数や関数にアクセス可能
    function handleClick(i){
        //squares配列のcopyを作成
        const nextSquares = squares.slice();
        nextSquares[i] = "X";
        setSquares(nextSquares);
    }

    return(
        <>
            <div className="board-row">
                <Square value={squares[0]} onSquareClick={()=> handleClick(0)} />
                <Square value={squares[1]} onSquareClick={()=> handleClick(1)} />
                <Square value={squares[2]} onSquareClick={()=> handleClick(2)} />
            </div>
            <div className="board-row">
                <Square value={squares[3]} onSquareClick={()=> handleClick(3)} />
                <Square value={squares[4]} onSquareClick={()=> handleClick(4)} />
                <Square value={squares[5]} onSquareClick={()=> handleClick(5)} />
            </div>
            <div className="board-row">
                <Square value={squares[6]} onSquareClick={()=> handleClick(6)} />
                <Square value={squares[7]} onSquareClick={()=> handleClick(7)} />
                <Square value={squares[8]} onSquareClick={()=> handleClick(8)} />
            </div>

        </>
    );
}
```

- なぜsquares.slice();を使ったのか
```
・アクションの取り消しを行いたい場合に助かる
・親のstateが変更されると子は自動で再レンダーされるので、copyを使うことでこれを回避することができる
```
- 手番の処理
```jsx
import {useState} from "react";

function Square({value, onSquareClick}){
    return <button className="square" onClick={onSquareClick}>
        {value}
    </button>;
}

export default function Board(){
    //手番
    const [xIsNext, setXIsNext] = useState(true);
    const [squares, setSquares] = useState(Array(9).fill(null));
    //squaresにアクセスできるのはclosureをsupportしているため
    //内側の関数は外側の関数で定義されている変数や関数にアクセス可能
    function handleClick(i){
        //squares配列のcopyを作成
        const nextSquares = squares.slice();
        if(xIsNext){
            nextSquares[i] = "X";
        }else{
            nextSquares[i] = "O";
        }
        setSquares(nextSquares);
        setXIsNext(!xIsNext); //真偽値反転
    }

    return(
        <>
            <div className="board-row">
                <Square value={squares[0]} onSquareClick={()=> handleClick(0)} />
                <Square value={squares[1]} onSquareClick={()=> handleClick(1)} />
                <Square value={squares[2]} onSquareClick={()=> handleClick(2)} />
            </div>
            <div className="board-row">
                <Square value={squares[3]} onSquareClick={()=> handleClick(3)} />
                <Square value={squares[4]} onSquareClick={()=> handleClick(4)} />
                <Square value={squares[5]} onSquareClick={()=> handleClick(5)} />
            </div>
            <div className="board-row">
                <Square value={squares[6]} onSquareClick={()=> handleClick(6)} />
                <Square value={squares[7]} onSquareClick={()=> handleClick(7)} />
                <Square value={squares[8]} onSquareClick={()=> handleClick(8)} />
            </div>

        </>
    );
}
```

- マス目に値が入っている場合の処理
```jsx
import {useState} from "react";

function Square({value, onSquareClick}){
    return <button className="square" onClick={onSquareClick}>
        {value}
    </button>;
}

export default function Board(){
    //手番
    const [xIsNext, setXIsNext] = useState(true);
    const [squares, setSquares] = useState(Array(9).fill(null));
    //squaresにアクセスできるのはclosureをsupportしているため
    //内側の関数は外側の関数で定義されている変数や関数にアクセス可能
    function handleClick(i){
        //既に値が入っていれば早期リターン
        if (squares[i]){
            return;
        }
        //squares配列のcopyを作成
        const nextSquares = squares.slice();
        if(xIsNext){
            nextSquares[i] = "X";
        }else{
            nextSquares[i] = "O";
        }
        //状態更新
        setSquares(nextSquares);
        setXIsNext(!xIsNext); //真偽値反転
    }

    return(
        //Boardの状態を使用しているので中身が書き換わる
        <>
            <div className="board-row">
                <Square value={squares[0]} onSquareClick={()=> handleClick(0)} />
                <Square value={squares[1]} onSquareClick={()=> handleClick(1)} />
                <Square value={squares[2]} onSquareClick={()=> handleClick(2)} />
            </div>
            <div className="board-row">
                <Square value={squares[3]} onSquareClick={()=> handleClick(3)} />
                <Square value={squares[4]} onSquareClick={()=> handleClick(4)} />
                <Square value={squares[5]} onSquareClick={()=> handleClick(5)} />
            </div>
            <div className="board-row">
                <Square value={squares[6]} onSquareClick={()=> handleClick(6)} />
                <Square value={squares[7]} onSquareClick={()=> handleClick(7)} />
                <Square value={squares[8]} onSquareClick={()=> handleClick(8)} />
            </div>

        </>
    );
}
```

- 勝者の宣言
```jsx
import {useState} from "react";

function Square({value, onSquareClick}){
    return <button className="square" onClick={onSquareClick}>
        {value}
    </button>;
}

export default function Board(){
    //手番
    const [xIsNext, setXIsNext] = useState(true);
    const [squares, setSquares] = useState(Array(9).fill(null));
    //squaresにアクセスできるのはclosureをsupportしているため
    //内側の関数は外側の関数で定義されている変数や関数にアクセス可能
    function handleClick(i){
        //値が入っているか、勝者が決まっているなら早期リターン
        if (squares[i] || calculateWinner(squares)){
            return;
        }
        //squares配列のcopyを作成
        const nextSquares = squares.slice();
        if(xIsNext){
            nextSquares[i] = "X";
        }else{
            nextSquares[i] = "O";
        }
        //状態更新
        setSquares(nextSquares);
        setXIsNext(!xIsNext); //真偽値反転
    }

    //勝者確認
    const winner = calculateWinner(squares);
    let status;
    if (winner){
        status = "Winner: " + winner;
    }else{
        status = "Next player: " + (xIsNext ? "X" : "O");
    }

    return(
        //Boardの状態を使用しているので中身が書き換わる
        <>
            <div className="status">{status}</div>
            <div className="board-row">
                <Square value={squares[0]} onSquareClick={()=> handleClick(0)} />
                <Square value={squares[1]} onSquareClick={()=> handleClick(1)} />
                <Square value={squares[2]} onSquareClick={()=> handleClick(2)} />
            </div>
            <div className="board-row">
                <Square value={squares[3]} onSquareClick={()=> handleClick(3)} />
                <Square value={squares[4]} onSquareClick={()=> handleClick(4)} />
                <Square value={squares[5]} onSquareClick={()=> handleClick(5)} />
            </div>
            <div className="board-row">
                <Square value={squares[6]} onSquareClick={()=> handleClick(6)} />
                <Square value={squares[7]} onSquareClick={()=> handleClick(7)} />
                <Square value={squares[8]} onSquareClick={()=> handleClick(8)} />
            </div>

        </>
    );
}

function calculateWinner(squares){
    const lines = [
        [0,1,2],
        [3,4,5],
        [6,7,8],
        [0,3,6],
        [1,4,7],
        [2,5,8],
        [0,4,8],
        [2,4,6]
    ];
    for (let i=0; i<lines.length; i++){
        const [a,b,c] = lines[i];
        //つまり、abcともに同じゲームならその記号を返す
        //そろっていなかったらnullを返す
        if(squares[a] && squares[a] === squares[b] && squares[a] === squares[c]){
            return squares[a];
        }
    }
    return null;
}
```

- 履歴保持
```jsx
import {useState} from "react";

function Square({value, onSquareClick}){
    return <button className="square" onClick={onSquareClick}>
        {value}
    </button>;
}

function Board({xIsNext, squares, onPlay}){
    function handleClick(i){
        //値が入っているか、勝者が決まっているなら早期リターン
        if (squares[i] || calculateWinner(squares)){
            return;
        }
        //squares配列のcopyを作成
        const nextSquares = squares.slice();
        if(xIsNext){
            nextSquares[i] = "X";
        }else{
            nextSquares[i] = "O";
        }
        onPlay(nextSquares);
    }

    //勝者確認
    const winner = calculateWinner(squares);
    let status;
    if (winner){
        status = "Winner: " + winner;
    }else{
        status = "Next player: " + (xIsNext ? "X" : "O");
    }

    return(
        //Boardの状態を使用しているので中身が書き換わる
        <>
            <div className="status">{status}</div>
            <div className="board-row">
                <Square value={squares[0]} onSquareClick={()=> handleClick(0)} />
                <Square value={squares[1]} onSquareClick={()=> handleClick(1)} />
                <Square value={squares[2]} onSquareClick={()=> handleClick(2)} />
            </div>
            <div className="board-row">
                <Square value={squares[3]} onSquareClick={()=> handleClick(3)} />
                <Square value={squares[4]} onSquareClick={()=> handleClick(4)} />
                <Square value={squares[5]} onSquareClick={()=> handleClick(5)} />
            </div>
            <div className="board-row">
                <Square value={squares[6]} onSquareClick={()=> handleClick(6)} />
                <Square value={squares[7]} onSquareClick={()=> handleClick(7)} />
                <Square value={squares[8]} onSquareClick={()=> handleClick(8)} />
            </div>

        </>
    );
}

function calculateWinner(squares){
    const lines = [
        [0,1,2],
        [3,4,5],
        [6,7,8],
        [0,3,6],
        [1,4,7],
        [2,5,8],
        [0,4,8],
        [2,4,6]
    ];
    for (let i=0; i<lines.length; i++){
        const [a,b,c] = lines[i];
        //つまり、abcともに同じゲームならその記号を返す
        //そろっていなかったらnullを返す
        if(squares[a] && squares[a] === squares[b] && squares[a] === squares[c]){
            return squares[a];
        }
    }
    return null;
}

export default function Game(){
    const [xIsNext, setXIsNext] = useState(true);
    //要素数が1つの配列を渡す
    const [history, setHistory] = useState([Array(9).fill(null)]);
    const currentSquares = history[history.length - 1];

    function handlePlay(nextSquares){
        //historyのすべての要素の後にnextSquaresが繋がった配列を作成
        setHistory([...history, nextSquares]);
        setXIsNext(!xIsNext);
    }
    return(
        <div className="game">
            <div className="game-board">
                <Board 
                xIsNext={xIsNext} 
                squares={currentSquares} 
                onPlay={handlePlay} />
            </div>
            <div className="game-info">
                <ol>{/*TODO*/}</ol>
            </div>
        </div>
    );
}
```

- 履歴に戻る
```
配列を別の配列に変換するためにmapメソッドを使う
[1,2,3].map((x) => x * 2)
```

- Jump機能の追加
```jsx
    const moves = history.map((squares, move)=>{
        let description;
        if (move > 0){
            description = "Go to move #" + move;
        }else{
            description = "Go top game start";
        }

        return (
            <li>
                <button onClick={()=> jumpTo(move)}>{description}</button>
            </li>
        );
    })
```

- 最終形態
```jsx
import {useState} from "react";

function Square({value, onSquareClick}){
    return <button className="square" onClick={onSquareClick}>
        {value}
    </button>;
}

function Board({xIsNext, squares, onPlay}){
    function handleClick(i){
        //値が入っているか、勝者が決まっているなら早期リターン
        if (squares[i] || calculateWinner(squares)){
            return;
        }
        //squares配列のcopyを作成
        const nextSquares = squares.slice();
        if(xIsNext){
            nextSquares[i] = "X";
        }else{
            nextSquares[i] = "O";
        }
        onPlay(nextSquares);
    }

    //勝者確認
    const winner = calculateWinner(squares);
    let status;
    if (winner){
        status = "Winner: " + winner;
    }else{
        status = "Next player: " + (xIsNext ? "X" : "O");
    }

    return(
        //Boardの状態を使用しているので中身が書き換わる
        <>
            <div className="status">{status}</div>
            <div className="board-row">
                <Square value={squares[0]} onSquareClick={()=> handleClick(0)} />
                <Square value={squares[1]} onSquareClick={()=> handleClick(1)} />
                <Square value={squares[2]} onSquareClick={()=> handleClick(2)} />
            </div>
            <div className="board-row">
                <Square value={squares[3]} onSquareClick={()=> handleClick(3)} />
                <Square value={squares[4]} onSquareClick={()=> handleClick(4)} />
                <Square value={squares[5]} onSquareClick={()=> handleClick(5)} />
            </div>
            <div className="board-row">
                <Square value={squares[6]} onSquareClick={()=> handleClick(6)} />
                <Square value={squares[7]} onSquareClick={()=> handleClick(7)} />
                <Square value={squares[8]} onSquareClick={()=> handleClick(8)} />
            </div>

        </>
    );
}

function calculateWinner(squares){
    const lines = [
        [0,1,2],
        [3,4,5],
        [6,7,8],
        [0,3,6],
        [1,4,7],
        [2,5,8],
        [0,4,8],
        [2,4,6]
    ];
    for (let i=0; i<lines.length; i++){
        const [a,b,c] = lines[i];
        //つまり、abcともに同じゲームならその記号を返す
        //そろっていなかったらnullを返す
        if(squares[a] && squares[a] === squares[b] && squares[a] === squares[c]){
            return squares[a];
        }
    }
    return null;
}

export default function Game(){
    const [xIsNext, setXIsNext] = useState(true);
    //要素数が1つの配列を渡す
    const [history, setHistory] = useState([Array(9).fill(null)]);
    const [currentMove, setCurrentMove] = useState(0); //現在が何番目の着手か
    const currentSquares = history[currentMove]; //現在の盤面状況

    function handlePlay(nextSquares){
        //historyの着手までを保持し、その後ろに付け加える。currentMoveが0なら0番目のみ保持される
        const nextHistory = [...history.slice(0, currentMove + 1), nextSquares];
        setHistory(nextHistory);
        setCurrentMove(nextHistory.length - 1);
        setXIsNext(!xIsNext);
    }

    //手番ボタンを押したときの処理
    function jumpTo(nextMove){
        //TODO
        setCurrentMove(nextMove); //着手を更新
        setXIsNext(nextMove %2 === 0); //手番を更新
    }
    //第1引数が処理中の要素、第2引数がidx
    const moves = history.map((squares, move)=>{
        let description;
        if (move > 0){
            description = "Go to move #" + move;
        }else{
            description = "Go top game start";
        }

        return (
            <li key={move}>
                <button onClick={()=> jumpTo(move)}>{description}</button>
            </li>
        );
    })
    return(
        <div className="game">
            <div className="game-board">
                <Board 
                xIsNext={xIsNext} 
                squares={currentSquares} 
                onPlay={handlePlay} />
            </div>
            <div className="game-info">
                <ol>{moves}</ol>
            </div>
        </div>
    );
}
```

- リファクタリング済み
```jsx
import {useState} from "react";

function Square({value, onSquareClick}){
    return <button className="square" onClick={onSquareClick}>
        {value}
    </button>;
}

function Board({xIsNext, squares, onPlay}){
    function handleClick(i){
        //値が入っているか、勝者が決まっているなら早期リターン
        if (squares[i] || calculateWinner(squares)){
            return;
        }
        //squares配列のcopyを作成
        const nextSquares = squares.slice();
        if(xIsNext){
            nextSquares[i] = "X";
        }else{
            nextSquares[i] = "O";
        }
        onPlay(nextSquares);
    }

    //勝者確認
    const winner = calculateWinner(squares);
    let status;
    if (winner){
        status = "Winner: " + winner;
    }else{
        status = "Next player: " + (xIsNext ? "X" : "O");
    }

    return(
        //Boardの状態を使用しているので中身が書き換わる
        <>
            <div className="status">{status}</div>
            <div className="board-row">
                <Square value={squares[0]} onSquareClick={()=> handleClick(0)} />
                <Square value={squares[1]} onSquareClick={()=> handleClick(1)} />
                <Square value={squares[2]} onSquareClick={()=> handleClick(2)} />
            </div>
            <div className="board-row">
                <Square value={squares[3]} onSquareClick={()=> handleClick(3)} />
                <Square value={squares[4]} onSquareClick={()=> handleClick(4)} />
                <Square value={squares[5]} onSquareClick={()=> handleClick(5)} />
            </div>
            <div className="board-row">
                <Square value={squares[6]} onSquareClick={()=> handleClick(6)} />
                <Square value={squares[7]} onSquareClick={()=> handleClick(7)} />
                <Square value={squares[8]} onSquareClick={()=> handleClick(8)} />
            </div>

        </>
    );
}

function calculateWinner(squares){
    const lines = [
        [0,1,2],
        [3,4,5],
        [6,7,8],
        [0,3,6],
        [1,4,7],
        [2,5,8],
        [0,4,8],
        [2,4,6]
    ];
    for (let i=0; i<lines.length; i++){
        const [a,b,c] = lines[i];
        //つまり、abcともに同じゲームならその記号を返す
        //そろっていなかったらnullを返す
        if(squares[a] && squares[a] === squares[b] && squares[a] === squares[c]){
            return squares[a];
        }
    }
    return null;
}

export default function Game(){
    //要素数が1つの配列を渡す
    const [history, setHistory] = useState([Array(9).fill(null)]);
    const [currentMove, setCurrentMove] = useState(0);
    const xIsNext = currentMove % 2 === 0;
    const currentSquares = history[currentMove];

    function handlePlay(nextSquares){
        //historyのすべての要素の後にnextSquaresが繋がった配列を作成
        const nextHistory = [...history.slice(0, currentMove + 1), nextSquares];
        setHistory(nextHistory);
        //現在の手番を配列の長さで決める
        setCurrentMove(nextHistory.length - 1);
    }

    function jumpTo(nextMove){
        //TODO
        setCurrentMove(nextMove);
    }
    //第1引数が処理中の要素、第2引数がidx
    const moves = history.map((squares, move)=>{
        let description;
        if (move > 0){
            description = "Go to move #" + move;
        }else{
            description = "Go top game start";
        }
        //renderした時に、keyでstateを維持する(兄弟間で一意であればいい)
        return (
            <li key={move}>
                <button onClick={()=> jumpTo(move)}>{description}</button>
            </li>
        );
    })
    //currentSquaresで現在の着手をrender
    return(
        <div className="game">
            <div className="game-board">
                <Board 
                xIsNext={xIsNext} 
                squares={currentSquares} 
                onPlay={handlePlay} />
            </div>
            <div className="game-info">
                <ol>{moves}</ol>
            </div>
        </div>
    );
}
```