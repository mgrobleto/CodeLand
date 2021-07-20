"use strict";
import ListDir from "./listDirUI/listDir.js";
import storage from './utils/storage.js'
import reducer from "./reducer/index.js";
import tabUI from "./tabUI/tab.js";

const data = window.__PRELOADED_STATE__;
const projectName = window.__PROJECT_NAME__;

delete window.__PRELOADED_STATE__;
delete window.__PROJECT_NAME__;

storage.createStore(reducer, [], projectName)

document.addEventListener("DOMContentLoaded", () => {
    const listDir = new ListDir(data, projectName);
    listDir.renderList();
    tabUI.render(storage.getStore());
});
