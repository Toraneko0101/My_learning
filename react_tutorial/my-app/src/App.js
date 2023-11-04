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

function Mytest(){
    const Items = [
        <h1>neko</h1>,
        <h1>inu</h1>,
    ];
    return(
        Items
    );
}

export default function MyApp(){
    return(
      <>
        <MyButton />
        <MyButton />
        <Mytest />
      </>
    );
}