'use strict'

const elements = document.querySelectorAll('#file')
const root_code = document.querySelector('#show_code')
const CURRENT_PATH = location.pathname
// const CURRENT_PATH = location.pathname.replace('/', '').split('/').slice(1, 3)

Array.prototype.forEach.call(elements, (element) => {
    element.addEventListener('click', async (event) => {
        console.log(CURRENT_PATH)
        const filename = event.currentTarget.dataset.filename
        const response = await fetch(`${CURRENT_PATH}`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                filename
            })
        })
        const data = await response.json()
        // const div = document.createElement('div')
        // const content = document.createTextNode()
        // div.appendChild(content)
        // document.body.insertBefore(div, root_code)
        root_code.innerHTML = data.info
    })
})
