class StorageCode {
    constructor() {

        if (StorageCode._instance) {
            return StorageCode._instance;
        }
        StorageCode._instance = this;
    }

    updateStore(state) {
        localStorage.setItem(this.projectName, state);
        this.storage = JSON.parse(state);
    }   

    // Actualiza la cantidad de tabs en la interfaz
    async dispatch (action) {
        const state = JSON.stringify(this.reducer(this.getStore(), action));
        this.updateStore(state)
    }

    createStore(reducer, initialState, projectName) {
        this.storage = JSON.parse(localStorage.getItem(projectName)) || initialState;
        localStorage.setItem(projectName, JSON.stringify(this.storage));
        this.projectName = projectName;

        this.reducer = reducer || (() => {});
    }

    getStore() {
        return this.storage;
    }
}

export default new StorageCode();
