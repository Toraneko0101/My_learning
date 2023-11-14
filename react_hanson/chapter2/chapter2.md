# React学習に必要なJSの知識

- JSの歴史
```
デビュー当時
    ・Webページを対話的にする目的
    ・buttonのclickやvalidationなど
DHTMLやAJAXの登場
    ・HTMLが動的に変化
    ・Ajaxで非同期通信
今日
    フルスタックなアプリ作成に耐えうる言語に
```

- JSの機能改善について
```
・ECMAという団体が言語仕様の変更を策定している
・0~4までの5段階のステージを経て、仕様に取り込まれるとのこと。ステージ0は提案で、4が仕様入りの決定。

・仕様を実装するかどうかは、ブラウザベンダにゆだねられている。
```

# 2.1 変数の定義

## 2.1.1 constキーワード(定数)

- 以前(全ての変数がvarだった)
```js
var pizza = true;
pizza = false
console.log(pizza)
```

## 2.1.2 letキーワード
```
・if文はスコープを持たない。そのためvarなら通ってしまう
・letならブロックの中から外を参照できなくなる。他の言語と同じ
```
- 例
```js
var topic = "JS";
if(topic){
    //var topic = "React";
    let topic = "React";
    console.log("inner", topic);
}
console.log("global", topic);
```

- 例2
```js
var div,
    container = document.getElementById("container");

for (var i=0; i<5; i++){
    div = document.createElement("div";
    div.onclick = function(){
        alert("This is box #" + i);
    };
    container.appendChild(div);
}
```
- 解説
```
以上のようにすると、iがグローバル変数なので初期化されて、常に#5が表示されてしまう。
```
- 修正版
```js
var div,
    container = document.getElementById("container");

//ループの繰り返しごとに異なるスコープが作成されるようになった
for (let i=0; i<5; i++){
    div = document.createElement("div");
    div.onclick = function(){
        alert("This is box #" + i);
    };
    container.appendChild(div);
}
```

## 2.1.3 テンプレート文字列
```js
//改行が維持されることに注意
const email = `
Hello ${firstName},

Thanks for ordering ${qty} tickets to ${event}.

Order Details

${firstName} ${middleName} ${lastName}
    ${qty} * $${price} = $${qty*price} to ${event}

You can pick your tickets up 30 minutes before
the show.

Thanks,

${ticketAgent}
`;
```

- HTMLを記載するのが容易に
```js
document.body.innerHTML = `
<section>
    <header>
        <h1>The React Blog</h1>
    </header>
    <article>
        <h2>${article.title}</h2>
        ${article.body}
    </article>
    <footer>
        <p>copyright ${new Date().getFullYear()} | The React Blog</p>
    </footer>
</section>
`;
```

# 2.2　関数の作成

## 2.2.1 関数宣言
```js
function hoge(){
    console.log("from now on, you are Sen");
}

hoge();
```

## 2.2.2 関数式
```js
const hoge = function(){
    console.log("extravagant name");
}

hoge();
```
- 2つの注意点
```
・関数宣言の場合は巻き上げが起きる
・つまり、宣言の前に呼び出しを記述可能
```

### 2.2.2.1 関数の引数
```js
const hoge = function(firstName){
    console.log(`You're doing great, ${firstName}`);
}

hoge("Tarou");
```

### 2.2.2.2 関数の戻り値
```js
const hoge = function(firstName, message){
    return `${firstName}: ${message}`;
}

hoge("Tarou", "I'm nyanko");
```

## 2.2.3　デフォルト引数
```js
//デフォルト引数はオブジェクトも設定可能
const defaultPerson = {
    name : {
        first : "Neko",
        last: "Nezumi"
    },
    pastime: "writing"
};

function hoge(person=defaultPerson){
    console.log(`${person.name.first} loves ${person.pastime}`);
}
```

## 2.2.4 アロー関数
```js
// 既存
const lordify = function(firstname){
    return `${firstName} of Canterbuty`;
};

console.log(lordify("Dale"))

//functionやreturn文なしで関数を記述可能
const lordify = (firstName, lastName ) => `${firstName} of Canterbuty`
```
- 解説
```
・イコールの後に引数
・引数が一つでないなら引数を囲むための括弧も省略可能
・アロー関数の本体に複数の命令を書きたい場合は{}で囲む。returnも書く
```

- 例
```js
const address = (firstName, land) =>{
    if(!firstName){
        throw new Error("A firstName required to address");
    }
    if(!land){
        throw new Error("A land is required to address");
    }
    return `${firstName} or ${land}`
};
console.log(address("Kelly", "Ingland"));
```

### 2.2.4.1 オブジェクトの返却
- 問題点
```
・アロー関数をインラインで書くには、戻り値のオブジェクトを括弧で囲む必要がある
```
```js
const person = (firstName, lastName) =>({
    first : firstName,
    last : lastName
});

console.log(person("Brad", "Janson"))
```

### 2.2.4.2 アロー関数とスコープ
```js
const tahoe = {
    mountains: ["Freel", "Rose", "Tallac", "Rubicon", "Silver"],
    print: function(delay = 1000){
        setTimeout(function(){
            console.log(this.mountails.join(", "));
            console.log(this);
        }, delay);
    }
};

tahoe.print();
```
- 解説
```
・関数宣言は独自のスコープを持つのでthisが指すものが変わってくる
・アロー関数の場合は、独自のスコープを持たないので、thisはtahoeを指したままになる。
・print関数自体をアロー関数にすると、thisはprint関数の外側のものを指すようになるので、失敗する

つまり
    ・thisの値は使われた場所によって左右される
    ・通常の関数内ならthisはグローバルオブジェクト
    ・関数がメソッドのコールバックとして使用される場合、thisはそのメソッドを呼び出したオブジェクトを参照する
    ・アロー関数の場合、そのアロー関数が定義されたスコープのthisを返す。
    ・オブジェクトのメソッド内ならthisはオブジェクト自体
    ・グローバルスコープなら、ブラウザの場合windowオブジェクト。Nodeの場合、globalオブジェクト
```
- アロー関数の例
```js
const tahoe = {
    mountains: ["Freel", "Rose", "Tallac", "Rubicon", "Silver"],
    print: function(delay = 1000){
        setTimeout(()=>{
            console.log(this.mountains.join(", "));
        }, delay);
    }
};

tahoe.print();
```

- thisの例
```js
const test = {
    prop : 42,
    func : function(){
        return this.prop;
    },
};

console.log(test.func());
```

# 2.3 Javascriptのコンパイル
```
・ブラウザで機能が実装される前に使いたい場合
・新しい構文で記述されたコードを、古い構文で記述されたコードに変換する
・この前工程は、コンパイル、またはトランスパイルと呼ばれる
```
- JSをコンパイルするためのツール
```
Babel
    ・この登場以降はコンパイルしてから実行するのが当然になった
```

- ES6 => ES5へのコンパイル
```js
const add = (x=5, y=10) => console.log(x+y); 

//Babelによる変換
"use strict"
var add = function add(){
    var x = 
        arguments.length <= 0 || arguments[0] === undefined ? 5 : arguments[0];
    var y = 
        arguments.length <= 1 || arguments[1] === undefined ? 5 : arguments[1];
    
    return console.log(x + y);
}
```
- 説明
```
"use strict"
    以降のコードがstricモードで実行されることを宣言
あとは、関数式に置き換えて、三項演算子で、デフォルト引数のロジックを再現している。
```

- Babel REPL
```
https://babeljs.io/repl
・JSを記述すると、コンパイルした結果を表示してくれる。
・BabelはwebpackやParcel等のツールに統合されており、通常の場合、コンパイルの処理はツールで自動化されている
・JSX等も変換してくれる
```

