# JSにおける関数型プログラミング
```
・Reactは関数型プログラミングの影響が色濃い
・サードパーティライブラリにもこれは当てはまる
```
- 関数型プログラミングの誕生
```
・ラムダ計算:
     1930年代
・高階関数という概念の導入: 
    引数として関数を受け取り、祖の関数をもとに別の関数を返す
・Lisp
    ラムダ計算のコンセプトを適用したプログラミング言語
    1950年代に誕生
    Lispにおける関数は第一級オブジェクト

第一級オブジェクト
    オブジェクトを関数の引数として渡したり戻り値として受け取れる場合の呼び名
```

# 3.1 関数型とは?
```
・JSにおいても関数は第一級オブジェクト
・つまり関数を変数と同様に扱える
・アロー関数やPromise,スプレッド構文などもこの流れにある
```
- 関数をほかのデータと同様に扱う
```
・関数はvar,let,constとともに宣言可能
・関数は変数と同様にオブジェクトのプロパティとして記述可能
```
- 例
```js
const obj = {
    message : "Neko",
    log(message){
        console.log(message);
    }
}

obj.log(obj.message);
```
- 配列に関数を格納する
```js
const messages = [
    "first index",
    message => console.log(message),
    "third index",
    message => console.log(message)
];

messages[1](messages[0]);
messages[3](messages[2]);
```
- 関数を別の関数に引数として渡す
```js
const insideFn =  logger =>{
    logger("This is logging message.");
}

insideFn(message => console.log(message));
//This is logging message.
```
- 関数の戻り値として関数を返却する
```js
const createScream = function(logger){
    return function(message){
        logger(message.toUpperCase() + "!!!");
    };
};

const scream = createScream(message => console.log(message));

scream("createScream returns a function");

/*
scream = ƒ (message){
        logger(message.toUpperCase() + "!!!");
    }

logger = message => console.log(message)
*/
```
- 上記の高階関数をアロー関数として書き直す
```js
const createScream = logger => message =>{
    logger(message.toUpperCase() + "!!!");
}

//複数の矢印が連続する関数は高階関数。
//関数がデータとして変数に格納可能で、アプリ内を自由に行き来できるのが、JSが関数型プログラミングと呼ばれる所以。
```

# 3.2 命令型 vs 宣言型
```
・関数型プログラミングは宣言型プログラミング
    ・何をするのかが重要(what)
    ・どのようにするかは重要ではない

従来のプログラミング言語はhowを記述する
    ・命令型プログラミング言語
```

- 例で考える(英文 to URL)
```js
//命令型
var string = "Restaurants in Hanalei";
var urlFriendly = "";

for(var i=0; i<string.length;i++){
    if(string[i] == ""){
        urlFriendly += "-";
    }else{
        urlFriendly += string[i];
    }
}
console.log(urlFriendly); //Restaurants-in-Hanalei

//命令型では、何をやりたいかは書かないので必然的に処理を説明するためのコメントを書くことになる
```
```js
//宣言型
const string = "Restaurants in Hanalei";
const urlFriendly = string.replace(/ /g, "-");

//正規表現を使うことで、文字列中の空白をすべてハイフンに変換すると記載した。つまり、宣言型プログラミングではコメントなしでやりたいことが分かる。
```

- 宣言型プログラミングの例
```js
const loadAndMapMembers = compose(
    combineWith(sessionStorage, "members"),
    save(sessionStorage, "members"),
    scopeMembers(window),
    logMemberInfoToConsole,
    logFieldsToConsole("name.first"),
    countMembersBy("location.state"),
    prepStatesForMagging,
    save(sessionStorage, "map"),
    renderUSMap
);

getFakeMembers(100).then(loadAndMapMembers);

//確かに何をしたいかはわかるかもしれない
//実装に関する詳細は、個々の関数により抽象化され隠蔽されている。
//これを組み合わせることでコメントを不要にする。
```

- 命令型でDOMを操作する
```js
const target = document.getElementById("target");
const wrapper = document.createElement("div");
const headline = document.createElement("h1");

wrapper.id = "welcome";
headline.innerText = "Hello world";

wrapper.appendChild(headline);
target.appendChiled(wrapper)

//このコードは行数が大きくなると変更が不便になる。
```
- 宣言的にDOMの操作を記述する
```js
const {render} = ReactDOM;

const welcome = () =>(
    <div id="welcome">
        <h1>Hello World</h1>
    </div>
);

render(<Welcome />, document.getElementById("target"));

//WelcomeはReactのcomponent
//表示されるべきDomの要素が記述されている
//render関数はDOMを構築して表示する
//上のコードではidがtargetである要素の下に、Welcomeコンポーネントを表示したいということがすぐわかる。
```

# 3.3 関数型プログラミングの基本概念

## 3.3.1 イミュータブルなデータ
```
・関数型プログラミングではすべてのデータはimmutable
・変更を加えることはできない？
・関数型プログラミングではデータに変更を加える際、必ずコピーを作成してから変更するらしい
```

- mutableの例
```js
let color_lawn = {
    title : "lawn",
    color : "#00FF00",
    rating : 0
};

//関数の引数としてobjを受け取っているので、
//実際のobjが参照されており、当然書き換えられる
function rateColor(color, rating){
    color.rating = rating;
    return color;
}
//colorを書き換えたものを返して、そのプロパティを参照する
console.log(rateColor(color_lawn, 5).rating);
console.log(color_lawn.rating) //5
```

- 原本を書き換えたくないのでimmutableにする(Object.assign)
```js
let color_lawn = {
    title : "lawn",
    color : "#00FF00",
    rating : 0
};
function rateColor(color, rating){
    return Object.assign({}, color, {rating: rating});
};

console.log(rateColor(color_lawn, 5).rating);
console.log(color_lawn.rating);
```

- 説明
```
Object.assignの第1引数に空オブジェクトを渡す
    ⇒新規に作成されたobjの方に対して変更を加えられる
    ⇒引数にはcolor_lawnを取っているが、元のobjの値は変更されない

```

- スプレッド構文を使って、簡潔にimmutableを作る(...でcopy作成)
```js
let color_lawn = {
    title : "lawn",
    color : "#00FF00",
    rating : 0
};

//objをrtnするので、()で囲むことに注意
const rateColor = (color, rating) =>({
    ...color,
    rating
})

console.log(rateColor(color_lawn, 5).rating);
console.log(color_lawn.rating);
```

- immutableな配列
```js
let list = [
    {title : "red"},
    {title : "lawn"},
    {title : "pink"}
];

//破壊的
// const addColor = function(title, colors){
//     colors.push({title : title});
//     return colors;
// }

// console.log(addColor("green", list).length);

//immutable(Array.concat)　新しい要素を受け取り配列に追加
const addColor = (title, array) => array.concat({title})
console.log(addColor("green", list).length);
console.log(list.length);

//スプレッド構文(list自体がrtnされる)
//スプレッド構文で新しいlistを作成し、その後ろにtitleを追加している感じ(cpしたものに追加しているのでもちろんimmutable)
const addColor = (title, list) => [...list, {title}];
console.log(addColor("green", list)[0]);
```

- 感想
```
スプレッド構文の方が直感的
```

## 3.3.2 純粋関数
```
純粋関数
    引数の値のみを参照し、それをもとに計算し値を返すもの
    副作用はなく、グローバル関数に値を書き込むことはない
    引数をimmutableなデータとして扱う
```

- ※純粋ではない関数
```js
const frederick = {
    name : "Frederick",
    canRead : false,
    canWrite : false
};

function selfEducate(){
    frederick.canRead = true;
    frederick.canWrite = true;
}

//関数の中身が変わってしまう
selfEducate();
console.log(frederick);
```

- 純粋関数(引数をimmutableにした)
```js
const frederick = {
    name : "frederick",
    canRead : false,
    canWrite : false
};

//...personを返している。そのうえで、属性を変化させている
const selfEducate = (person) => ({
    ...person,
    canRead: true,
    canWrite: true
})

console.log(selfEducate(frederick));
console.log(frederick);
```

- DOMを操作する例で考える
```js
//純粋ではない書き方

function Header(text){
    let h1 = document.createElement("h1");
    h1.innerText = text;
    document.body.appendChild(h1);
}

Header("ヘッダ関数は副作用を発生させる");
```
- Reactの場合
```
・上記の場合は、関数内でDOMに変更を加えており、副作用がある
・ReactはUIコンポーネントが純粋関数として表現される
・例は下に示す通り
・作成した要素を戻り値として返却しており、関数内でappendChildなどをしていない。要素の使用法は上位のアプリにゆだねられている
```
```js
const Header = props => <h1>{props.title}</h1>
```

- 純粋関数の利点と注意点
```
1. アプリケーションの状態を変更しないという利点がある
2. 純粋関数は関数型プログラミングの中心的概念である
3. 純粋関数はテストを容易にする。⇒環境に変更を加えないので

4. 関数は少なくとも一つの引数を受け取る必要があり、また引数以外の値を参照してはいけない
5. 関数は値もしくは他の関数を戻り値として返却する必要がある
6. 関数は引数や関数外で定義された変数に直接変更を加えてはならない
```

## 3.3.3 データの変換
```
・関数型プログラミングではアプリのデータは変化しない
・個々の関数はdataのコピーを作成し、それに変更を加えて、変更を加えたコピーを別の関数に渡していく
```

- データ変換のためにArray.mapとArray.reduceを使う
```js
const schools = ["Waseda", "Tokyo", "Hokkaido"];
//Array.joinは非破壊的
console.log(schools.join(", "));

//Array.filterで絞り込む
const wSchools = schools.filter(school => school[0] === "W");
console.log(wSchools);
```
- Array.filterの説明
```
・配列のサブセットを新しい配列として返す
・predicateを引数にとる

predicate
    ・引数に配列の要素を取る
    ・真偽値を返すコールバック関数
    ・それぞれの要素ごとにpredicateが呼ばれる
    ・predicateの戻り値が要素を最終的にサブセットに吹く前るかどうかを決めるために使用される

配列から要素を削除する際
    Array.pop, Array.splice => 破壊的
    Array.filter => 非破壊的
```

- Array.filterで配列から要素を削除する例
```js
const schools = ["Waseda", "Tokyo", "Hokkaido"];
const cutSchool = (cut, list) =>{
    //listの要素を1つずつをschoolに代入
    return list.filter(school => school !== cut);
};

console.log(cutSchool("Hokkaido", schools).join(", "));
```

- Array.map
```
・コールバック関数を引数にとる
・コールバック関数は配列の要素の数だけ呼び出される
・戻り値は新しい配列に追加される
```
```js
schools = ["Neko", "Nezumi", "Inu"];
const highSchools = schools.map(school => `${school} High School `);
console.log(highSchools.join("\n"));
// Neko High School 
// Nezumi High School 
// Inu High School 
console.log(schools.join("\n"));
// Neko
// Nezumi
// Inu
```
- Array.mapを使って、オブジェクトの配列を作成する
```js
schools = ["Neko", "Nezumi", "Inu"];
//objを返すので()で囲んでいる。返したものを集めてlistを作る
const highSchools = schools.map(school => ({name : school}));
console.log(highSchools);
// [
//     {name : "Neko"},
//     {name : "Nezumi"},
//     {name : "Inu"},
// ]
```
- 配列のうち、1つの要素だけを変更する
```js
const schools = [
    {name : "Maibara"},
    {name : "Hogehoge"},
    {name : "Umintyu"}
];

//三項演算子を使って簡潔に書く
const editName = (oldName, name, arr) =>
    arr.map(item => (
        item.name === oldName ? 
        {...item, name} :
        item
    ));
// const editName = (oldName, name, arr) =>{
//     return arr.map(item =>{
//         //mapに対してreturnする
//         if(item.name == oldName){
//             return {
//                 ...item,
//                 name : name // name
//             };
//         }else{
//             return item;
//         }
//     });
// }

const updatedSchools = editName("Hogehoge", "Fugafuga", schools);
console.log(updatedSchools[1]);
// {name: 'Fugafuga'}
console.log(schools[1]);
// {name: 'Hogehoge'}

```
- オブジェクトから配列を得る
```js
//Array.map + Object.keys(objに含まれるすべてのキーを配列として返す)

const animals = {
    Neko: 12,
    Nezumi : 3,
    Nekomata: 113
};

//keys(配列)に対してmapを行っているだけ
const animalArray = Object.keys(animals).map(key =>({
    name : key,
    ages : animals[key] //val
}));

console.log(animalArray);
// [
//   {name: 'Neko', ages: 12}
//   {name: 'Nezumi', ages: 3}
//   {name: 'Nekomata', ages: 113}
// ]
```
- 配列から単一の値への変換
```js
//Array.reduceを使う(Array.reduceRight:配列を末尾から走査)
const ages = [4,23,123,43,321,12];
const MaxAge = ages.reduce((max, age)=>{
    console.log(`${age} > ${max} = ${age > max}`);
    if(age > max) return age;
    else return max;
}, 0);
console.log("maxAge", MaxAge);

/*
const result = array.reduce((prevValue, currentValue, currentIndex, array) =>{
    return prevValue
}, initialValue)
*/

//returnされた値が、次の第一引数に入る感じ
const ages = [4,23,123,43,321,12];
const MaxAge = ages.reduce((max, age, index, ages)=>{
    console.log(index);
    if(age > max) return age;
    else return max;
},0)
console.log(MaxAge);
```
- Array.reduceで配列をobjに変換する

```js
const colors = [
    {
        id: "xekare",
        title : "rad red",
        rating : 3
    },
    {
        id : "jbwsof",
        title : "big blue",
        rating : 2
    },
    {
        id : "nekoneko",
        title : "banana",
        rating : 1
    }
];

const hashColors = colors.reduce((hash, {id, title, rating})=>{
    hash[id] = {title, rating};
    return hash;
}, {});
console.log(hashColors);
```
- 説明
```
・今回は初期値が空オブジェクト{}
・オブジェクトに対してプロパティ値を、ブラケット表記を使って代入。
```

- 配列を異なる配列に変換
```js
const colors = ["red", "red", "green", "blue", "green"];

const uniqueColors = colors.reduce(
    (unique, color) =>
        unique.indexOf(color) !== -1 ? unique : [...unique, color],
        []
);

console.log(uniqueColors);
```
- 説明
```
・初期値が[]
・unique.indexOf(color)でunique内にcolorがなければ-1になる。
・つまり、あればそのままuniqueを返し、なければ、要素を追加したものを返す
・結果的に重複が取り除かれた配列が生成できた
```