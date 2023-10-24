import * as MiniCraft from 'MiniCraft';
import * as x from "./hello.js";

MiniCraft.log("Hello from test.js", x.hello());


class MyPlugin {
    constructor() {
        this.name = "My Plugin";
        MiniCraft.log("My Plugin constructor");
    }

    onLoad() {
        MiniCraft.log("My Plugin loaded!");
    }
}



MiniCraft.loadPlugin(MyPlugin)