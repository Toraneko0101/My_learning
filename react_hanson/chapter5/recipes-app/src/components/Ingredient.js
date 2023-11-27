import React from "react";

/**
 * デストラクチャリングを用いて、propsオブジェクトから
 * amount, measurement, nameのデータを抽出
 */
export default function Ingredient({amount, measurement, name}){
    return(
        <li>
            {amount} {measurement} {name}
        </li>
    );
}