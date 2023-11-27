var path =  require("path");

/**
 * entryファイルを指定:ここを起点にimportをparseする
 * output: 出力先を指定 ./dist/assets/bundle.js
 */
module.exports = {
    entry: "./src/index.js",
    output: {
        path: path.join(__dirname, "dist", "assets"),
        filename: "bundle.js"
    },

    module:{
        rules: [{ test: /\.js$/, exclude: /node_modules/, loader: "babel-loader"}]
    },
    devtool : "inline-source-map"
};