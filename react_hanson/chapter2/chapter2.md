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

# 2.4 オブジェクトと配列

## 2.4.1 デストラクチャリング
```
デストラクチャリング
    ・オブジェクトを変数に代入したり、引数として受け取る際に、
    　必要なプロパティのみ取捨選択できる機能
```

- 例
```js
const sandwich = {
    bread: "yamazaki",
    meat: "beef",
    cheese: "swiss",
    toppings: ["tomato", "orange"]
};

const {bread, meat} = sandwich;
console.log(bread, meat);
```
- 説明
```
オブジェクトを分解して、
通常プロパティとしてsandwich.breadと取らなければいけなかったものを
ローカル変数に代入している。
代入の際は別のキーワード（たとえばlet）を使ってもよい

```

- 関数の引数にデストラクチャリングを使う
```js
//本来だったらprint = regularPersonで,${regularPerson.firstname}としていたので簡潔になっている
const print = ({firstname}) =>{
    console.log(`firstname is ${firstname}`);
}

const regularPerson = {
    firstname: "Bill",
    lastname : "Wilson"
};
//呼ぶときは関数名
print(regularPerson);
```

- オブジェクトの深いレベルのプロパティを、デストラクチャリングで簡単にアクセスする
```js
const regularPerson = {
    firstname: "Bill",
    lastname : "wilson",
    features : {
        race: "human",
        height: "174cm"
    }
};

const hoge = ({features : {race}}) =>{
    console.log(`race is ${race}`);
};

hoge(regularPerson);
```

- 説明
```
{features : {race}}のように波括弧をネストさせてプロパティを指定することで、
オブジェクトの深部にあるプロパティを選択して取得可能
```

## 2.4.2 配列のデストラクチャリング
```js
const [firstElement] = ["Neko", "Inu", "Nezumi"];
console.log(firstElement);
//カンマで不要な要素を読み飛ばす
a = ["Neko", "Inu", "Nezumi"]
const [, , thirdElement] = a;
console.log(thirdElement);

```

## 2.4.3 オブジェクトリテラルの改善
- プロパティ名の省略
```js
//変数をオブジェクトのプロパティ値として記述する場合、プロパティ名の省略が可能に
//関数もそのままプロパティとして記述可能
const name = "Neko";
const age = 134;
const print = function(){
    console.log(`Mister ${this.name} is ${this.age} years old.`);
}
const data = {name: name, age: age};
const data2 = {name, age, print};
data2.print();
```
- オブジェクト内に関数を記載する際の、function省略
```js
name = "Neko";
height = 173;
const Animal = {
    name,
    height,
    fuga(){
        let upper = this.name.toUpperCase();
        console.log(upper);
    }
};
Animal.fuga();
```

## 2.4.4 スプレッド構文
- 配列の連結
```js
const peaks = ["Fuji", "Tateyama", "Kinkazan"];
const vallay = ["Kurobe", "Geibikei", "Kawaura"];
const Nature = [...peaks, ...vallay];//この時点でリスト連結
console.log(Nature.join(", "))

```
- イミュータブルな配列の実現
```js
const peaks = ["Fuji", "Tateyama", "Kinkazan"];
//const [last] = peaks.reverse(); 
const [last] = [...peaks].reverse();
//reverseは破壊的な処理なので、[...peaks]でコピーを作成し、
//これをreverseすることで防ぐ
console.log(last);
console.log(peaks.join(", "))
```

- 配列の残り要素を表現する
```js
const lakes = ["kawanaka", "towada", "biwa", "hamana"];
const [first, ...others] = lakes;
console.log(others.join(", "));
```

- 関数の引数を配列として受け取る・残余引数
```js
function directions(...args){
    let [start, ...remaining] = args;
    let [finish, ...stops] = remaining.reverse();

    console.log(`drive through ${args.length} towns`);
    console.log(`start in ${start}`);
    console.log(`finish is ${finish}`);
    console.log(`stopping city is ${stops.join(", ")}`);
} 

directions("Okinawa", "Ooita", "Hokkaido","Gihu");
```

- オブジェクトで見るスプレッド構文
```js
//中身を一度に受け取れている
const morning = {
    breakfast: "oatmeal",
    lunch : "peanut butter and strawberry jum"
};

const dinner = "mac and cheese burger";
const backpackingMeals = {
    ...morning,
    dinner
};

console.log(backpackingMeals);
```

# 2.5 JavaScriptと非同期処理
```js
//同期処理
const neko = document.querySelector("#neko");
neko.innerHTML = "Nyanko!";

//データベースアクセス,API呼びだし、映像や音楽再生など
//待ちが発生する処理は非同期で実行される必要がある
```

## 2.5.1 Promiseとfetch
```
fetch
    HTTPのリクエストを送信してresponseを受信するためのJS API
    REST APIの呼び出し簡潔化の立役者

console.log(fetch("https://api.randomuser.me/?nat=US&results=1"));
    戻り値をログ出力すると、APIのレスポンスではなく、Pending(保留中)のPromiseオブジェクトが確認できる

Promise
    Resolved:成功
    Pending:保留
    Rejected:失敗

    ・保留中はデータ取得が完了していない状態を示す
    ・thenメソッドを使うことでメソッドチェーンを記述できる
    ・thenメソッドはコールバック関数を引数にとる
    ・直前の非同期処理が成功するとコールバックがよばれる
    ・コールバック関数でさらに戻り値を返した場合は、Promiseチェーンの次のthenのコールバック関数に引き継がれる
```

- コールバックの例
```js
//1. randomuser.meにGETリクエストを送信
//2. 呼び出しが成功すればresponseのbody文字列をJSONオブジェクトに変換
//3. JSONオブジェクトのresultsプロパティを取りだす
//4. 取り出した値をコンソール出力
//5. どこかでエラーが発生したらconsole.errorでコンソールにエラー出力
fetch("https://api.randomuser.me/?nat=US&results=1")
    .then(res => res.json())
    //.then(json =>{
    //     console.log(json.results);
    // })
    .then(json => json.results)
    .then(console.log)
    .catch(console.error);
```

## 2.5.2 async/await
```
async
    ・非同期関数を同期関数のように呼び出せる
    ・Promiseオブジェクトを受け取り、thenメソッドで値を取り出す代わりにawaitキーワードを書く
    ⇒Promiseが成功するまで処理は待たされる
```
- 例
```js
//catchブロックがないと、エラーが発生した場合PromiseStateエラーとなる
//awaitで呼び出した非同期関数内でPromiseが失敗する可能性が
//あるときは、関数呼び出しをtry/catchで囲む
const getFakePerson = async () => {
    try{
       const res = await fetch("https://api.randomuser.me/?nat=US&results=1");
       const {results} = await res.json();
       console.log(results);
    }catch(error){
        console.error(`Failed to fetch: ${error}`);
    }
};

getFakePerson();
```
- 注意
```
Cross-Origin Resource Sharing
    ・異なるオリジンからのリソースへのアクセスをブラウザは制限する。
    ・つまり、ホスト名とポート番号の組み合わせ（オリジン）が異なるページで上記のURL関連のfetchをするとCORSがセキュリティ制限の件で怒ってくる
```

## 2.5.3 Promiseの生成
```
・データを取得するために複数のAPIを呼び出す必要がある場合エラーの種類が複数あるが、そのような状態を単純化したい
```

- AJAXの呼び出しを、Promiseオブジェクトにラップ
```js
const getFakeMemvers = count =>
    //Promiseを返す。1つのオブジェクトなので{}はなし。
    new Promise((resolves, rejects) =>{
        const api = `https://api.randomuser.me/?nat=US&results=${count}`;
        const request = new XMLHttpRequest();
        request.open("GET", api);
        request.onload = () =>
            //200ならresolvesを呼ぶ
            request.status == 200
                ? resolves(JSON.parse(request.response).results)
                : reject(Error(request.statusText));
            request.onerror = err => rejects(err);
            request.send();
    })

//then/catchメソッドによるエラー処理
getFakeMembers(5)
    .then(members => console.log(members))
    .catch(error => console.error(`getFakeMembers failed: ${error.message}`));

//try/catchによるエラー処理
async function testGetFakeMembers(){
    try{
        const members = await getFakeMembers(5);
        console.log(members)
    }catch (error){
        console.error(`getFakeMembers failed: ${error.message}`);
    }
}
```

# 2.6 クラス宣言
```
・JSでは全てのオブジェクトはプロトタイプと呼ばれるプロパティを持つ。プロパティを用いて継承が実現される⇒プロトタイプ継承
```
- classキーワードを使用しないカスタムクラス
```js
function Vacation(destination, length){
    this.destination = destination;
    this.length = length;
}

Vacation.prototype.print = function(){
    console.log(this.destination + " | " + this.length + " days");

}
var maui = new Vacation("Maui", 7);
maui.print();
```
- 解説
```
new演算子でインスタンス化される際に、初期値を受け取る
Vacationはprintというメソッドを持つが
インスタンスはprototypeオブジェクト上にあるprintを継承するので以上のような奇妙な書き方になる
```

- classキーワードを使ったもの
```js
class Vacation{
    constructor(destination, length){
        this.destination = destination;
        this.length = length;
    }

    print(){
        console.log(`${this.destination} will take ${this.length} days.`)
    }
}

const trip = new Vacation("Santiago", 21);
trip.print();
```
- 注意点
```
classキーワードは糖衣構文
    内部的には依然としてクラスの実態はコンストラクタ関数
    prototypeにより継承が実現される
```

- extendsで継承する
```js
class Expedition extends Vacation{
    constructor(destination, length, gear){
        super(destination, length);
        this.gear = gear;//listが入る
    }

    print(){
        super.print();
        console.log(`Bring your ${this.gear.join(" and your ")}`)
    }
    
}

//呼び出し
const trip = new Expedition("Mt.Whitney", 3,[
    "one",
    "tow",
    "three"
]);

trip.print();
```

# 2.7 ECMAScriptモジュール
```
・jsにとって、モジュールは再利用可能なコード
・他のjsファイルからimportして使う
・個々のモジュールは別のファイルに格納されており、名前空間が独立しているので、モジュール間で変数名が重複していても衝突は起きない。
・一つのモジュールから複数のオブジェクトをexportすることも可能
```

- 二つのオブジェクトをエクスポートする例
```js
/*./two_obj*/
export const print = message => log(message, date());
export const log = (message, timestamp) =>
    console.log(`${timestamp.toString()}: ${message}`);
//引数はなし
const date = () => new Date();
```
- 単一のオブジェクトをエクスポートする例
```js
/*./one_obj */
export default new Expedition("Neko", 2, ["water", "orange"]);
```

- import側のコード
```js
import {print , log } from "./two_obj";
import freel from "./one_obj";

print("print message");
log("logging message");
freel.print();
```
- defaultキーワードの意味
```
・defaultがない方では、デストラクチャリングを使用して複数の値を受け取っている。
・defaultの方では、単一の変数を使ってimportされている。またimportする名前は上記の通り、任意のもので許される
⇒import側が自由に設定できるので、リファクタリングしにくい
```
- defaultがなくとも、asを使えば別名で可能
```js
import {print as p, log as l} from "./two_obj";
p("print message");
l("logging a message");
```

- exportされたすべての値を単一のオブジェクトで受け取る
```js
import * as fns from "./two_obj";
// fns.print(), fns.log();
```
- 説明
```
importとexportはESMと呼ばれる仕様の一部
全ての機能が実装されていない場合はBabelを使って吸収する
```

## 2.7.1 CommonJSモジュール
```
・ECMAScriptモジュールが登場する前からNode.jsではCommonJSというモジュールパターンが採用されていた。
・BabelやwebpackではこのCommonJSがサポートされている
・CommonJSではmodule.exportsという特別なオブジェクト経由でモジュールをexportする
```
- CommonJSモジュールとして、先ほどのprint関数をexportする
```js
//export
const print = message => log(message, new Date());
const log = (message, timestamp) =>
    console.log(`${timestamp.toString()}: ${message}`);

module.exports = {print, log};

//import 
const {log, print} = require("./hoge.js")
```
- 説明
```
・import時には、require関数を使う
```