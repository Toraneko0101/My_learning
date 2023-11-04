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