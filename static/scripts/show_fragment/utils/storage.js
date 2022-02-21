class StorageCode {
    constructor() {

        if (StorageCode._instance) {
            return StorageCode._instance;
        }
        StorageCode._instance = this;
    }

    updateStore(state) {
        localStorage.setItem(this.fragmentName, state);
        this.storage = JSON.parse(state);
    }   

    // Actualiza la cantidad de tabs en la interfaz
    async dispatch (action) {
        const state = JSON.stringify(this.reducer(this.getStore(), action));
        this.updateStore(state)
    }

    createStore(reducer, initialState, fragmentName) {
        this.storage = JSON.parse(localStorage.getItem(fragmentName)) || initialState;
        localStorage.setItem(fragmentName, JSON.stringify(this.storage));
        this.fragmentName = fragmentName;

        this.reducer = reducer || (() => {});
    }

    getStore() {
        return this.storage;
    }
}

export default new StorageCode();
