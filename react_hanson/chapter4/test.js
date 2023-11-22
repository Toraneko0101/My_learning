const items = [
    "salt butter",
    "peanut butter",
    "brown sugar",
    "eggs",
    "flour",
    "teaspoon salt"
];

//デストラクチャリング
function IngredientsList({items}){
    return React.createElement(
        "ul",
        {className : "ingredients"},
        items.map((ingredient, i)=>{
            return React.createElement("li", {key : i}, ingredient)
        })
    );
} 

ReactDOM.render(
    //itemsプロパティに分離したデータを設定:第二引数はプロパティ
    React.createElement(IngredientsList, {items}, null),
    document.querySelector("#root")
);