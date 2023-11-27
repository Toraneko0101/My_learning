import React from "react";
import Ingredient from "./Ingredient";

{/*ingredientsがlistとして渡される */}
export default function IngredientsList({list}){
    return(
        <ul className = "ingredients">
            {/* スプレッド構文で、ingredientの全プロパティを渡している*/}
            {/*Ingredientに値を渡す */}
            {list.map((ingredient, i)=>(
                <Ingredient key={i} {...ingredient} />
            ))}
        </ul>
    );
}