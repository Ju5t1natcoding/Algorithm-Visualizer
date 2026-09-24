document.addEventListener('DOMContentLoaded', function() {
    const year_elem = document.getElementById("curr_year");

    if (year_elem) {
        year_elem.textContent = new Date().getFullYear();
    }

    const scroll_links = document.querySelectorAll('a[href^="#"]');
    scroll_links.forEach(link => {
        link.addEventListener('click', function(ev) {
            const target_id = this.getAttribute('href');

            if (!target_id || target_id === '#') {
                return;
            }

            const target_elem = document.querySelector(target_id);

            if (!target_elem) {
                return;
            }

            ev.preventDefault();
            target_elem.scrollIntoView({behaviour: smooth, block: start});
        });
    });
});