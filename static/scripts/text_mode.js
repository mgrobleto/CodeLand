window.scrollTo(0, 70);
const $options = document.querySelectorAll('.option-explorer');
const $btnAll = document.querySelector('[data-filter-projects="all"]');
const $btnUser = document.querySelector('[data-filter-projects="user"]');
const $btnDefault = document.querySelector('[data-filter-projects="default"]');
const $projectsSection = document.querySelector('#projects-section');

function templateProjectDefault(img, name) {
    return (`
        <img src="${img}" id="conteinerImg">
        <div class="project-info">
            <h5>${name}</h5>
            <a class="btn btn-primary bezel-btn" href="/static_projects/text_mode/${name}" role="button">Ver código</a>
        </div>
    `)
}

function templateProjectUser(img, author, projectName, id) {
    return (`
            <img src="${img}" id="conteinerImg">
            <div class="project-info">
                <h5>${projectName}</h5>
                <p style="color: #aaa;">${author}</p>
                <a class="btn btn-primary bezel-btn" href="/project/${author}/${id}" role="button">Ver código</a>
            </div>
    `)
}

$btnAll.addEventListener('click', async function () {
    const $filter = this.dataset.filterProjects;
    $options.forEach((option) => {
        option.classList.remove('active');
    })
    this.classList.add('active');
    const response = await fetch(`/projects/text_mode/${$filter}`)
    const find = await response.json()
    $projectsSection.innerHTML = ''
    find.data.default.forEach((project) => {
        const $project = document.createElement('div');
        $project.className = 'project'
        $project.innerHTML = templateProjectDefault(project.image, project.program_title);
        $projectsSection.appendChild($project);
    })
    find.data.user.forEach((project) => {
        const $project = document.createElement('div');
        $project.className = 'project'
        $project.innerHTML = templateProjectUser(project.image, project.author, project.project_name, project._id);
        $projectsSection.appendChild($project);
    })
})

$btnUser.addEventListener('click', async function () {
    const $filter = this.dataset.filterProjects;
    $options.forEach((option) => {
        option.classList.remove('active');
    })
    this.classList.add('active');
    const response = await fetch(`/projects/text_mode/${$filter}`)
    const find = await response.json()

    console.log(find)
    $projectsSection.innerHTML = ''
    find.data.forEach((project) => {
        const $project = document.createElement('div');
        $project.className = 'project'
        $project.innerHTML = templateProjectUser(project.image, project.author, project.project_name, project._id);
        $projectsSection.appendChild($project);
    })
})

$btnDefault.addEventListener('click', async function () {
    const $filter = this.dataset.filterProjects;
    $options.forEach((option) => {
        option.classList.remove('active');
    })
    this.classList.add('active');
    const response = await fetch(`/projects/text_mode/${$filter}`)
    const find = await response.json()

    console.log(find)
    $projectsSection.innerHTML = ''
    find.data.forEach((project) => {
        const $project = document.createElement('div');
        $project.className = 'project'
        $project.innerHTML = templateProjectDefault(project.image, project.program_title);
        $projectsSection.appendChild($project);
    })
})
