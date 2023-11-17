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