function recordsTable() {
    let records = Object.keys(localStorage).sort((a,b) => localStorage[b] - localStorage[a]);

    for (let i=0;  i<localStorage.length ;i++) {
        if(records[i]!=="username"&& records[i]!==undefined&& records[i]!=="undefined") {
            let tablebody = document.getElementById('tablebody');
            let row = document.createElement("TR");
            tablebody.appendChild(row);

            let td1 = document.createElement("TD");
            let td2 = document.createElement("TD");

            row.appendChild(td1);
            row.appendChild(td2);
            td1.innerHTML = records[i];
            td2.innerHTML = localStorage[records[i]];

        }
    }
}

recordsTable();