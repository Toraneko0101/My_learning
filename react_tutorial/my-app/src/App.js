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