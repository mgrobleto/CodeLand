'use strict'

const $formList = document.querySelectorAll('#delete-project')
const $project = document.querySelector('#projects')

function renderTemplate(project) {
    return `
    <div class='col col-lg-4'>
    <div class='card' style='width: 18rem;'>
        <img src="data:image/${project.contentType};base64,${atob(project.image.$binary)}" alt="${project.title}">
        <div class='card-body'>
            <h5 class='card-title'>${project.title}</h5>
            <p class='card-text'>
                ${project.description}
            </p>
            <a href='/project/${user.username}/${project.title}' class='btn btn-primary'>Ver y editar</a>
            <form id="delete-project">
                <input type="hidden" name="id" value="${project._id.$oid}">
                <button class='btn btn-danger'>Borrar proyecto</button>
            </form>
        </div>
    </div>
</div>
    `.trim()
}

Array.prototype.forEach.call($formList, function ($form) {
    $form.addEventListener('submit', async (event) => {
        event.preventDefault()
        const formData = new FormData(event.currentTarget)
        const response = await fetch(`/delete-project`, {
            method: 'DELETE',
            body: formData
        })
        const { data, delete_info} = await response.json()
        const code = ''
        $project.innerHTML = ''
        console.log(JSON.parse(data))
        console.log(delete_info)
        for(const project of JSON.parse(data)) {
            code += renderTemplate(project)
        }
        $project.innerHTML = code
    })
})
