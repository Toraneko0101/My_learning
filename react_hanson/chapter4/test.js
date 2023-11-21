const items = [
    "2 lb salmon",
    "5 sprigs fresh rosemary",
    "2 tablespoons olive oil",
    "2 small lemons",
    "1 teaspoon kosher salt",
    "4 cloves of chopped garlic"
    ];
    //配列の要素を別の要素の子要素に設定する場合、
    //配列の各要素はkeyプロパティを持つ必要がある
    //keyはユニークである必要がある。
const test = React.createElement(
    "ul",
    {className : "ingredients"},
    items.map((ingredient, i) =>
            React.createElement("li", {key: i}, ingredient))
);

ReactDOM.render(test, document.querySelector("#root"));