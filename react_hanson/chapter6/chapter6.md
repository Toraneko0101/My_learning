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