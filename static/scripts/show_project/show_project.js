"use strict";
import ListDir from "./listDirUI/listDir.js";
import storage from './utils/storage.js'
import reducer from "./reducer/index.js";
import tabUI from "./tabUI/tab.js";
import './settings.js'

const data = window.__PRELOADED_STATE__;
const projectName = window.__PROJECT_NAME__;
const depthDir = window.__DIR_DEPTH__;

delete window.__PRELOADED_STATE__;
delete window.__PROJECT_NAME__;
delete window.__DIR_DEPTH__;

storage.createStore(reducer, [], projectName)

document.addEventListener("DOMContentLoaded", () => {
    const listDir = new ListDir(data, projectName, depthDir);
    listDir.renderList();
    tabUI.render(storage.getStore());
});
