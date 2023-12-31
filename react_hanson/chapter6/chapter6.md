# ステート管理
- プロパティとステート
```
・Reactのコンポーネントはデータがなければただの箱
・コンポーネントはツールでしかない
・前章ではプロパティを受け渡す方法を習ったが、プロパティはRead-Only。コンポーネントの描画後は変更されない
・コンポーネントの描画後に変更されるデータをステートという
・ステートを導入することで、既存のレシピの変更削除、追加のUIを提供可能。
・特定のステートの変更が、他のコンポーネントのプロパティに伝わり、最終的に必要な部分を変更するといった構造を持つ
```

- この章でやること
```
・フォームのデータを入力するためのコンポーネントをステートを使って実装する。
```

# 6.1 StarRatingコンポーネント
```
・レーティングのUIを提供するコンポーネントを実装する
```
- 星のアイコンを表示するためのパッケージ
```
$ npm i react-icons
```
- Font Awesomeが提供する星のアイコン(FaStar)を使用する
```js
import React from "react";
import {FaSter} from "react-icons/fa";

export default function StarRating(){
    return [
        <FaSter color="red" />,
        <FaSter color="red" />,
        <FaSter color="red" />,
        <FaSter color="grey" />,
        <FaSter color="grey" />
    ];
}
```
- 説明
```
react-iconsからimportされたFaSterコンポーネントを利用して、星のアイコンのSVGを5つ描画している
```

- 選択中の星は赤色に、非選択の色はグレーにする
```js
import React from "react";
import {FaStar} from "react-icons/fa";

const Star = ({selected = false}) =>(
    <FaStar color={selected ? "red" : "gray"} />
);

function StarRating({totalStars = 5}){
    return [...Array(totalStars)].map((_, i) => <Star key={i} />);
}

export default StarRating;
```
- 説明
```
[...Array(n)]
    ・サイズnの配列をinlineで作成するコード
    ・[...Array(5)]ならundefinedの要素が5つ作られる
    ・これに対してmapを呼び出すと、個々の要素の値はundefinedなので無視され、indexだけが参照される

```

## 6.1.1 useStateフックを使ってclickに対応
```
・Ratingは描画後も変化する値なのでStateとして実装する
・関数コンポーネントでステートを実装する場合は、Reactが提供するフックという機能を使う

フック
    ・コンポーネントに対して着脱可能な機能を取り付けるイメージ
    ・自作のフックを定義することも可能
    ・Reactはたくさんのbuilt-inフックを持っている

useState
    ・コンポーネントにステートを追加したいときに使う
```
- コード
```js
import React, {useState} from "react";
import {FaStar} from "react-icons/fa";

const Star = ({selected = false}) =>(
    <FaStar color={selected ? "red" : "gray"} />
);

function StarRating({totalStars = 5}){
    //ステートの現在値が格納
    const [selectedStars] = useState(3);
    //JSXの要素を含んだ配列を{}で囲むと、配列の要素が表示される
    //単一の要素の場合は、()で囲まれていることになるので要らなかったはず
    return (
        <>
            {
                [...Array(totalStars)].map((n, i)=>(
                    <Star key={i} selected={selectedStars > i} />
                ))
            }
            <p>
                {selectedStars} of {totalStars} stars
            </p>
        </>
    );
}

export default StarRating;
```
- onClickイベントハンドラを設定する
```js
const Star = ({selected = false, onSelect = f => f}) =>(
    <FaStar color={selected ? "red" : "gray"} onClick={onSelect} />
);
```
- 解説
```
f => f
    ・受け取った値をそのまま返すダミー関数
    ・クリックした際に、onClick関数がundefinedであるとエラーになるので、デフォルト引数を設定している
    ・直近のブラウザではonClickイベントにundefinedを設定してもエラーにならないっぽい
```

- Clickイベントを反映したステート
```js
import React, {useState} from "react";
import {FaStar} from "react-icons/fa";

const Star = ({selected = false, onSelect = f => f}) =>(
    <FaStar color={selected ? "red" : "gray"} onClick={onSelect} />
);

//onselectではclosureとして親のローカル関数iを保持しているので、
//clickすると適切な値でsetSelectedStarsが呼び出される
function StarRating({totalStars = 5}){
    const [selectedStars, setSelectedStars] = useState(0);
    return (
        <>
            {
                [...Array(totalStars)].map((n, i)=>(
                    <Star 
                    key={i} 
                    selected={selectedStars > i} 
                    onSelect={() => setSelectedStars(i + 1)}
                    />
                ))
            }
            <p>
                {selectedStars} of {totalStars} stars
            </p>
        </>
    );
}

export default StarRating;
```
- 解説
```
const [selectedStars, setSelectedStars] = useState(0);
    ・2番目の要素は関数。
    ・この関数を使ってコンポーネント内からステート値を変更可能
    ・デストラクチャリングでuseStateの戻り値を2つの変数に代入している
    ・setSelectedStarsを呼び出すことで、コンポーネントは再描画される。つまり、StarRating関数が呼び出され、結果selectedStarsには更新されたステート値が代入される。

★データが変更されると、フックは自身がフックされたコンポーネントを新しいデータで再描画する能力を持つ

例)
・先頭から2番目のStarコンポーネントをClickする
・onSelect関数が参照しているiの値は1なので、setSelectedStarsには2がsetされる。
・StarReatingコンポーネントは再描画され、selectedStarsに2が代入される。
```
[hooksのstateが見られる画像](./images/star1.png)

- 昔のステート管理
```
・昔はクラスコンポーネントにステートオブジェクトを追加する必要があった
・フックと比べて構文は複雑で、コンポーネント間でのコードの再利用も難しかった
・thisやbindが各所に用いられている
```

## 6.1.2 再利用性を考慮したリファクタリング
```
ユーザはstyleを変更したいと思うかも
    ・ReactコンポーネントにCSSを適用するにはstyleプロパティ経由で行う。
    ・多くのコンポーネントはプロパティ経由で受け取ったstyle値を、自身が描画する要素に反映させる
    ・styleプロパティは子要素に渡すようにする

ユーザはイベントハンドラを設定したいと思うかも
    ・propsプロパティの残りの引数をそのまま<div>要素に渡す

ただし
    ・propsに<div>がサポートしないプロパティが入っていたり
    ・不正なプロパティがpropsに含まれている場合
    ⇒失敗する
    ⇒その場合は、明示的にpropsがイベントハンドラを抽出する

```
```js
import React, {useState} from "react";
import {FaStar} from "react-icons/fa";

const Star = ({selected = false, onSelect = f => f}) =>(
    <FaStar color={selected ? "red" : "gray"} onClick={onSelect} />
);

//i+1なので0をclickすると1になる
//外側の波括弧はJSXを埋め込むためのもの。内側の必要性を疑ったときは本来、style={color: "yellow"}という風に表記することを思い出す。
function StarRating({style = {}, totalStars = 5, ...props}){
    const [selectedStars, setSelectedStars] = useState(0);
    return (
        <div style={{padding : "5px", ...style }} {...props}>{/*styleプロパティを受け取って、さらにpaddingを追加している */}
            {
                [...Array(totalStars)].map((n, i)=>(
                    <Star 
                    key={i} 
                    selected={selectedStars > i} 
                    onSelect={() => setSelectedStars(i + 1)}
                    />
                ))
            }
            <p>
                {selectedStars} of {totalStars} stars
            </p>
        </div>
    );
}

export default StarRating;
```
# 6.2 アプリケーション全体のステート管理
```
・複数のコンポーネントがステートを持つと、機能追加やデバッグが難しくなる。
・アプリケーションのステートは1か所で管理した方が効率的
・分かりやすいのは最上位のルートコンポーネントですべてのステートを管理し、子供にプロパティ値として渡すことで、全体に反映させるやり方
・以下に、本章で使用するデータを示す
```
- data
```json
[
    {
        "id": "0175d1f0-a8c6-41bf-8d02-df5734d829a4",
        "title": "ocean at dusk",
        "color": "#00c4e2",
        "rating": 5
    },
    {
        "id": "83c7ba2f-7392-4d7d-9e23-35adbe186046",
        "title": "lawn",
        "color": "#26ac56",
        "rating": 3
    },
    {
        "id": "a11e3995-b0bd-4d58-8c48-5e49ae7f7f23",
        "title": "bright red",
        "color": "#ff0000",
        "rating": 0
    }
]
```
## 6.2.1 ステート値をコンポーネントツリーの上から下に伝える
```
・ルートコンポーネントAppでステートを保持する
・ステート値はjsonから読みだして、配下のcomponentに渡す
・配下ではステートを保持しない
・ColorDataがステートの初期値になる。
・これをColorListにプロパティ値として渡す
```
- App.js
```js
import React, {useState} from "react";
import colorData from "./color_data.json";
import ColorList from "./ColorList.js";

export default function App(){
    const [colors] = useState(colorData);
    return <ColorList colors={colors} />;
}
```
- ColorList.js
```js
import React from "react";
import Color from "./Color";

/**
 * 1.Appのcomponentから渡されたプロパティからcolorsの配列を取り出す
 * 2.colorsが長さ0ならmessage出力
 * 3.それ以外はColorコンポーネントの配列に変換して、配列なので{}でくくってJSXとしてreturnする
 */
export default function ColorList({colors = []}){
    if(!colors.length) return <div>No Colors Listed.</div>
    return (
        <div>
            {
                colors.map(color => <Color key={color.id} {...color} />)
            }
        </div>
    );
}
```
- Color.js
```js
import StarRating from "./StarRating"
/**
 * 3つのpropertyを受け取る
 * ratingについてはStarRatingのpropertyとして渡す
 */

export default function Color({title, color, rating}){
    return (
        <section>
            <h1>{title}</h1>
            <div style={{height: 50, backgroundColor: color}} />
            <StarRating selectedStars={rating} />
        </section>
    )
}
```
- StarRating.js
```js
/**
 * rootで持っているので、starRatingはstateを保持する必要がなくなった
 * そのため同じプロパティ値で呼び出されたら必ず同じ描画結果となる⇒純粋関数
 * 自身でstateを管理しながら、親のstateをpropertyとして受け取ることも可能
 */
import {FaStar} from "react-icons/fa";

const Star = ({selected = false, onSelect = f => f}) =>(
    <FaStar color={selected ? "red" : "gray"} onClick={onSelect} />
);

export default function StarRating({totalStars = 5, selectedStars = 0}){
    return (
        <>
            {
                [...Array(totalStars)].map((n, i)=>(
                    <Star 
                    key={i} 
                    selected={selectedStars > i} 
                    />
                ))
            }
            <p>
                {selectedStars} of {totalStars} stars
            </p>
        </>
    );
}
```

## 6.2.2 ユーザの操作をコンポーネントツリーの下から上に伝える
```
・変更や削除などのユーザの操作は末端のコンポーネントに対して行われる
・それをrootに伝える必要がある。rootコンポーネントに対してstateが保持されているので
・以下では色タイトルの隣に削除ボタンを配置して、特定の色をstateから削除できるようにする
```

- StarRating.js
```js
/**
 * rootで持っているので、starRatingはstateを保持する必要がなくなった
 * コンポーネントを実装したときにiを持つ
 */
import {FaStar} from "react-icons/fa";

const Star = ({selected = false, onSelect = f => f}) =>(
    <FaStar color={selected ? "red" : "gray"} onClick={onSelect} />
);

export default function StarRating({
    totalStars = 5, 
    selectedStars = 0,
    onRate = f => f //色の評価用
}){
    return (
        <>
            {
                [...Array(totalStars)].map((n, i)=>(
                    <Star 
                    key={i} 
                    selected={selectedStars > i}
                    onSelect={()=> onRate(i+1)}
                    />
                ))
            }
            <p>
                {selectedStars} of {totalStars} stars
            </p>
        </>
    );
}
```
- Color.js
```js
import {FaTrash} from "react-icons/fa"; //ゴミ箱のアイコン
import StarRating from "./StarRating"
/**
 * 1. 3つのpropertyを受け取る
 * 2. ratingについてはStarRatingのpropertyとして渡す
 * 3. buttonのclick時に、onRemove関数が呼び出される。idプロパティをclosureで参照
 * colorコンポーネントは、親にイベントを通知する
 * onRemoveは、引数として親から受け取っているので責任は、親に転嫁できる
 */

export default function Color({
    id,
    title, 
    color, 
    rating, 
    onRemove = f => f,
    onRate = f => f
}){
    return (
        <section>
            <h1>{title}</h1>
            <button onClick={()=> onRemove(id)}>
                <FaTrash />
            </button>
            <div style={{height: 50, backgroundColor: color}} />
            <StarRating 
                selectedStars={rating}
                onRate={(rating) => onRate(id, rating)} 
            />
        </section>
    )
}
```
- ColorList.js
```js
import React from "react";
import Color from "./Color";

/**
 * 1.Appのcomponentから渡されたプロパティからcolorsの配列を取り出す
 * 2.colorsが長さ0ならmessage出力
 * 3.それ以外はColorコンポーネントの配列に変換して、配列なので{}でくくってJSXとしてreturnする
 * onRemoveColorの実装は親
 */
export default function ColorList({
    colors = [], 
    onRemoveColor = f => f,
    onRateColor = f => f
}){
    if(!colors.length) return <div>No Colors Listed.</div>
    return (
        <div>
            {
                colors.map(color => 
                <Color 
                    key={color.id} 
                    {...color} 
                    onRemove={onRemoveColor}
                    onRate={onRateColor} 
                />)
            }
        </div>
    );
}
```
- App.js
```js
import React, {useState} from "react";
import colorData from "./color_data.json";
import ColorList from "./ColorList.js";

/**
 * onRemoveColor
 *  idを引数にとり、対応する色のデータをstateの配列colorsから除外して新しい配列を生成。その後、setColorsでcomponentを再描画 
 * onRateColor
 *  id,ratingを引数にとり、idに対応するratingを新しい値で更新。その後、再描画
 */
export default function App(){
    const [colors, setColors] = useState(colorData);
    return (
      <ColorList 
      colors={colors}
      onRemoveColor = {id => {
        const newColors = colors.filter(color => color.id !== id);
        setColors(newColors);
      }} 
      onRateColor={(id, rating) =>{
        const newColors = colors.map(color=>{
          return color.id === id ? {...color, rating} : color
        });
        setColors(newColors);
      }}
      />
    );
}

```

# 6.3 フォーム入力を処理するアプリケーション
```
・色を追加するUIを実装する
・通例、form要素はinputやbutton等の子要素を持つ
```
## 6.3.1 refを使ったデータアクセス
```
ref:
    ・コンポーネントの描画結果であるDOMノードへの参照を保持する
    ・useRefフックを関数コンポーネント内で呼び出すことで使える
    ・今回はこれを用いてフォームを実装する

```

- 制御されていないコンポーネント
```js
//DOMに直接アクセスし、取得や変更を行っている(React以外のライブラリとデータをやり取りするとき以外はやめた方がいい)
import React, {useRef} from "react";

export default function AddColorForm({onNewColor = f => f}){
    //title入力用の<input>要素を参照するためのref_object
    //refに設定することで、ref_obj.currentでDOM要素に直接アクセス可能
    
    const txtTitle = useRef();
    //色の選択用の<input>要素を参照するためのref_object
    const hexColor = useRef();
    //ADDボタンがクリックされたタイミングでDOM要素にアクセスし、入力値を読みだす
    const submit = (e) => {
        e.preventDefault(); //ボタンクリック時のPOST送信:default動作を抑止
        const title = txtTitle.current.value; //ユーザの入力値を取得
        const color = hexColor.current.value;
        onNewColor(title, color); //親に通知
        txtTitle.current.value = "";
        hexColor.current.value = "";
    };

    return (
        <form onSubmit = {submit}>
            <input ref={texTitle} type="text" placeholder="color title..." required />
            <input ref={hexColor} type="color" required />
            <button>ADD</button>
        </form>
    );
}
```

## 6.3.2 制御されたコンポーネント
```
・ユーザの入力値はReactで管理されるので、DOMノードに対する直接アクセスは不要。refも不要
```
- AddColorForm.js
```js
import React, {useRef} from "react";

export default function AddColorForm({onNewColor = f => f}){
    const [title, setTitle] = useState("");
    const [color, setColor] = useState("#000000");

    const submit = e => {
        e.preventDefault();
        onNewColor(title, color);
        setTitle("");
        setColor("#000000");
    };
    //ユーザが文字をタイプするたびに、stateを更新する仕組みが必要
    //変わるたびに、valueの値をsetしている
    /**
     * カラーの方は、ユーザがマウスドラッグするたびに再描画される
     * しかし、Reactは重複した描画要求を調停する仕組みを持っている
     * ただ、関数自体は呼び出されるので描画関数内で重い処理を実行するのは避けるべき
     */
    return(
        <form onSubmit={submit}>
            <input
                value={title}
                onChange={event => setTitle(event.target.value)}
                type="text"
                placeholder="color title..."
                required
            />
            <input
                value={color}
                onChange={event => setColor(event.target.value)}
                type="color"
                required
            />
            <button>ADD</button>
        </form>
    );
}
```

## 6.3.3　カスタムフック
```
・巨大なフォームを実装する場合、input要素を大量に書くことになる
・重複したコードを切り出して抽象化したい。孫田ときに役立つのがカスタムフック
```
- hooks.js
```js
import {useState} from "react";

/**
 * stateの初期値を受け取り、配列を戻り値として返す
 * 1つ目はvalueとonChangeのプロパティ名：値を含むオブジェクト
 * 2つ目はstateを初期値でリセットするための関数
 */
export const useInput = initialValue =>{
    const [value, setValue] = useState(initialValue);
    return [
        {value, onChange: e => setValue(e.target.value)},
        () => setValue(initialValue)
    ];
};
```

- AddColorForm.js
```js
import React from "react";
import {useInput} from "./hooks";

export default function AddColorForm({onNewColor = f => f}){
    const [titleProps, resetTitle] = useInput("");
    const [colorProps, resetColor] = useInput("#000000");

    const submit = e => {
        e.preventDefault();
        //引数はこっちで書くけど、関数は親で定義
        onNewColor(titleProps.value, colorProps.value);
        resetTitle();
        resetColor();
    };

    /**
     * {...titleProps}には、useInputから返ってきたvalueとset用の関数が入っていた配列があり、デストラクチャリングで取り出している
     * resetTitleには、() => setValue(initialValue)が入っている最初にuseInputを""で初期化しているので、() => setValue("")ということになる
     */
    return(
        <form onSubmit={submit}>
            <input 
                {...titleProps}
                type="text"
                placeholder="color title..."
                required
            />
            <input
                {...colorProps}
                type="color"
                required 
            />
            <button>ADD</button>
        </form>
    );
}
```

## 6.3.4 入力をステート値に反映させる
```
・更新した際は、関数プロパティ経由で親に通知する
・親で関数を定義し、子の方でその関数を使って引数を入れる感じ
```
- App.js
```js
import React, {useState} from "react";
import colorData from "./color_data.json";
import ColorList from "./ColorList.js";
import AddColorForm from "./AddColorForm.js";
import {v4} from "uuid"; //ランダムなuuid


/**
 * onRemoveColor
 *  idを引数にとり、対応する色のデータをstateの配列colorsから除外する。その後、setColorsでcomponentを再描画 
 * onRateColor
 *  id,ratingを引数にとり、idに対応するratingを新しい値で更新。その後、再描画
 * setColors
 *  新しく配列をsetしている
 */
export default function App(){
    const [colors, setColors] = useState(colorData);
    return (
      <>
        <AddColorForm
          onNewColor={(title, color)=>{
            const newColors = [
              ...colors,
              {
                id : v4(),
                rating: 0,
                title,
                color
              }
            ];
            setColors(newColors);
          }} 
        />
        <ColorList 
          colors={colors}
          onRemoveColor = {id => {
            const newColors = colors.filter(color => color.id !== id);
            setColors(newColors);
          }} 
          onRateColor={(id, rating) =>{
            const newColors = colors.map(color=>{
              return color.id === id ? {...color, rating} : color
            });
            setColors(newColors);
          }}
        />
      </>
    );
}

```

# 6.4 Reactコンテキスト
```
・ルートコンポーネントでのみステートを保持する方法は、アプリケーションの規模が大きくなり、ネストが深くなると非現実的になった
・ステートを1か所で管理するには、ルートと末端のcomponentでプロパティをすべて設定しなければいけないため
・中間のコンポーネントはデータの受け渡しのために、使いもしないデータを上位や下位に流す必要があるので、コードは複雑になりスケールも大変になる。
・中継地を利用しない方法がコンテキスト
```
- contextの概要
```
・これを利用するには、まずコンテキストプロバイダーにデータを渡す
・これは特別なcomponentで、コンポーネントツリーの全体もしくは一部を、このコンポーネントで囲む
・コンテキストコンシューマーはコンテキストからデータを読み出すのにつかわれる
・コンテキストを利用することで、アプリケーションのステートは1か所で管理され、コンポーネントを経由する必要もなくなる
```
- index.js
```js
//コンテキストプロバイダーを追加する
import React, {createContext} from 'react';
import {render} from 'react-dom';
import App from "./App";
import colors from "./color_data.json"

/**
 * 
 * ColorContext
 *  exportされている。そのためcolorsのデータを参照したい場合は、AppコンポーネントからColorContext.Consumerをimportする必要がある
 * ColorContext.Provider
 *  アプリケーションのデータを渡し、ルートのAppを囲む
 *  渡されたアプリケーションのデータcolorsはApp配下のすべてのコンポーネントから参照可能
 * ColorContext.Consumer
 * 
 * 一部のcomponent二のみデータを公開したい場合は、コンポーネントツリーの一部をProviderで囲む
 * アプリケーション内で複数のContext.Providerを使うことも可能
 */
export const ColorContext = createContext();

render(
  <ColorContext.Provider value={{ colors }} >
    <App />
  </ColorContext.Provider>,
  document.getElementById("root")
);



```

- App.js
```js
import React from "react";
import ColorList from "./ColorList.js";
import AddColorForm from "./AddColorForm";

export default function App(){
  return(
    <>
      <AddColorForm />
      <ColorList />
    </>
  ); 
}
```

## 6.4.2 useContextフックからデータを取得する
```
useContext
    ・内部でコンテキストのConsumerコンポーネントを使用してデータを取得している
    ・コンテキストから直接データにアクセスしよう
```

- ColorList.js
```js
import React, { useContext } from "react";
import Color from "./Color";
import {ColorContext} from "./";

export default function ColorList(){
    const {colors} = useContext(ColorContext);
    if(!colors.length) return <div>No Colors Listed. (Add a Color)</div>
    return (
        <div>
            {
                colors.map(color => <Color key={color.id} {...color} />)
            }
        </div>
    );
}
```

- useContext以前
```js
/**
 * フックが登場する前はConsumerコンポーネントにアクセスする必要があり
 * Consumer内でレンダープロップというパターンを用いてコンテキストにアクセスしていた
*/
export default function ColorList(){
    return(
        <ColorContext.Consumer>
            {context => {
                if(!context.colors.length)
                return <div>No Colors Listed. (Add a Color)</div>;
                    return (
                        <div className="color-list">
                        {
                            context.colors.map(color =>{
                                <Color key={color.id} {...color} />
                            })
                        }
                        </div>
                    );
            }}
        </ColorContext.Consumer>
    )
}
```

## 6.4.3 コンテキストとステートの併用
```
・コンテキストプロバイダーを使うとデータの公開が可能
・データの変更には更に親のコンポーネントの助けがいる
・親でステートを保持して、その値をProviderコンポーネントに設定
・ステートが更新されると親が再描画され、結果的にProvider配下のコンポーネントツリーが再描画される
・ステートを保持するコンポーネントでコンテキストプロバイダーを描画する場合、そのコンポーネントをカスタムプロバイダーとよぶ
```
- ColorProvider.js(カスタムプロバイダー)
```js
import React, {createContext, useState} from "react";
import colorData from "./color-data.json";

export const ColorContext = createContext();

/**
 * children配下のcomponentはcolorsの参照が可能
 * setColorsもコンテキストに設定しているので、ステート値の変更も可能
 * setColorsを呼び出して変更すると、ColorProviderコンポーネントが再描画され、新しいcolorsの値でその配下も含めて再描画される(useStateがフックされているのはColorProviderなので)
 */
export default function ColorProvider({children}){
    const [colors, setColors] = useState(colorData);
    //valueにはobjを渡す
    return(
        <ColorContext.Provider value={{colors, setColors}}>
            {children}
        </ColorContext.Provider>
    );
}
```

- 改良
```
・setColors関数をそのままコンテキストで公開すると、どんな操作も可能になる。
・そのため特定の関数のみをコンテキストに設定するようにする
```
- ColorProvider.js
```js
import React, {createContext, useState} from "react";
import colorData from "./color-data.json";

export const ColorContext = createContext();

/**
 * children配下のcomponentはcolorsの参照が可能
 * setColorsの代わりに特定の関数のみを引き渡す
 * 今回の場合、3つの関数はコンテキスト経由でどこからでも参照可能
 */
export default function ColorProvider({children}){
    const [colors, setColors] = useState(colorData);
    //valueにはobjを渡す
    const addColor = (title, color) =>
        setColors([
            ...colors,
            {
                id: v4(),
                rating: 0,
                title,
                color
            }
        ]);

    const rateColor = (id, rating) =>
        setColors(
            colors.map(color => (color.id === id ? {...color, rating} : color))
        );
    
    const removeColor = id => setColors(colors.filter(color => color.id !== id));

    return(
        <ColorContext.Provider value={{colors, addColor, removeColor, rateColor}}>
            {children}
        </ColorContext.Provider>
    );
}
```
## 6.4.4 コンテキストとカスタムフックの併用
```
・カスタムフックを導入すればコンテキストをコンシューマに公開せず、データの共有が可能
・コンテキストの操作をカスタムフックで隠蔽することで、コンポーネントの開発者にコンテキストの知識がない場合でもデータの共有が可能
・具体的にはColorContextの代わりに、カスタムフックをimportする
```
- ColorProvider.jsのhead(6)
```js
import React, {createContext, useState, useContext} from "react";
import colorData from "./color-data.json";
import {v4} from "uuid";

const ColorContext = createContext();
export const useColors = () => useContext(ColorContext);
```
- 説明
```
・コンテキストにはカスタムフック経由でアクセスされる
・useContextはカスタムフック内で呼び出される
・そのためColorContextを別途exportする必要はない
・つまり、ColorProvider.jsはColorProviderとuseColorsフックをexportする

・useContexの戻り値は、指定したcontextの現在の値となる
・この値は、ツリー内でuseContextを呼び出したcomponentの上位かつ最も近いContext.Providerに渡されたvalueとして決定される。
・今回は、valueにオブジェクトを設定し、そこからデストラクチャリングで必要な値（関数）だけ取り出している
```

- 最終結果
- ColorProvider.js
```js
import React, {createContext, useState, useContext} from "react";
import colorData from "./color_data.json";
import {v4} from "uuid";

const ColorContext = createContext();
export const useColors = () => useContext(ColorContext);

/**
 * children配下のcomponentはcolorsの参照が可能
 * setColorsの代わりに特定の関数のみを引き渡す
 * providerコンポーネントはvalueプロパティを受け取り、それが子孫であるconsumerコンポーネントに渡される
 */
export default function ColorProvider({children}){
    const [colors, setColors] = useState(colorData);
    //以下,setColorsで値を変える用の関数3種
    const addColor = (title, color) =>
        setColors([
            ...colors,
            {
                id: v4(),
                rating: 0,
                title,
                color
            }
        ]);

    const rateColor = (id, rating) =>
        setColors(
            colors.map(color => (color.id === id ? {...color, rating} : color))
        );
    
    const removeColor = id => setColors(colors.filter(color => color.id !== id));

    return(
        <ColorContext.Provider value={{colors, addColor, removeColor, rateColor}}>
            {children}
        </ColorContext.Provider>
    );
}
```
- index.js
```js
//コンテキストプロバイダーを追加する
import React from 'react';
import ColorProvider from "./ColorProvider";
import {render} from 'react-dom';
import App from "./App";

//colorcontext.providerはcolorprovider.jsの方でreturnされる
//reactではchildrenは特殊なpropsであり、親タグの間に書かれたコード全体を意味する
//つまり今回の場合、ColorProviderのchildrenはAppである
//本コードではAppはその子要素として他のコンポーネントを持つので、ColorProviderは全てのコンポーネントを囲んでいることになる。
render(
  <ColorProvider>
    <App />
  </ColorProvider>,
  document.getElementById("root")
);
```
- App.js
```js
import React from "react";
import ColorList from "./ColorList.js";
import AddColorForm from "./AddColorForm";

export default function App(){
  return(
    <>
      <AddColorForm />
      <ColorList />
    </>
  ); 
}
```
- ColorList.js
```js
import React from "react";
import Color from "./Color";
import {useColors} from "./ColorProvider";

export default function ColorList(){
    const {colors} = useColors(); //useColors = () => useContext(ColorContext);
    if(!colors.length) return <div>No Colors Listed. (Add a Color)</div>
    return (
        <div>
            {
                colors.map(color => <Color key={color.id} {...color} />)
            }
        </div>
    );
}
```
- Color.js
```js
import {FaTrash} from "react-icons/fa"; //ゴミ箱のアイコン
import React from "react";
import StarRating from "./StarRating"
import {useColors} from "./ColorProvider";

/**
 * useColors()からカスタムフック経由で関数を取得している。
 */
export default function Color({id, title, color, rating }){
    const {rateColor, removeColor} = useColors();
    return (
        <section>
            <h1>{title}</h1>
            <button onClick={()=> removeColor(id)}><FaTrash /></button>
            <div style={{height: 50, backgroundColor: color}} />
            <StarRating 
                selectedStars={rating}
                onRate={(rating) => rateColor(id, rating)} 
            />
        </section>
    );
}
```
- StarRating.js
```js
/**
 * rootで持っているので、starRatingはstateを保持する必要がなくなった
 * コンポーネントを実装したときにiを持つ
 */
import {FaStar} from "react-icons/fa";
import {useColors} from "./ColorProvider";

const Star = ({selected = false, onSelect = f => f}) =>(
    <FaStar color={selected ? "red" : "gray"} onClick={onSelect} />
);

export default function StarRating({
    totalStars = 5, 
    selectedStars = 0,
    onRate = f => f //色の評価用
}){
    const {rateColor} = useColors();
    return (
        <>
            {
                [...Array(totalStars)].map((n, i)=>(
                    <Star 
                    key={i} 
                    selected={selectedStars > i}
                    onSelect={()=> rateColor(i+1)}
                    />
                ))
            }
            <p>
                {selectedStars} of {totalStars} stars
            </p>
        </>
    );
}
```
- AddColorForm.js
```js
import React from "react";
import {useInput} from "./hooks";
import {useColors} from "./ColorProvider";
export default function AddColorForm(){
    const [titleProps, resetTitle] = useInput("");
    const [colorProps, resetColor] = useInput("#000000");
    const { addColor } = useColors();

    const submit = e => {
        e.preventDefault();
        addColor(titleProps.value, colorProps.value);
        resetTitle();
        resetColor();
    };

    /**
     * {...titleProps}には、useInputから返ってきたvalueとset用の関数が入っていた配列があり、デストラクチャリングで取り出している
     * resetTitleには、() => setValue(initialValue)が入っている最初にuseInputを""で初期化しているので、() => setValue("")ということになる
     */
    return(
        <form onSubmit={submit}>
            <input 
                {...titleProps}
                type="text"
                placeholder="color title..."
                required
            />
            <input
                {...colorProps}
                type="color"
                required 
            />
            <button>ADD</button>
        </form>
    );
}
```
- hook.js
```js
import {useState} from "react";

/**
 * stateの初期値を受け取り、配列を戻り値として返す
 * 1つ目はvalueとonChangeのプロパティ名：値を含むオブジェクト
 * 2つ目はstateを初期値でリセットするための関数
 */
export const useInput = initialValue =>{
    const [value, setValue] = useState(initialValue);
    return [
        {value, onChange: e => setValue(e.target.value)},
        () => setValue(initialValue)
    ];
};
```