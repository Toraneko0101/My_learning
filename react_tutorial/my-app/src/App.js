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