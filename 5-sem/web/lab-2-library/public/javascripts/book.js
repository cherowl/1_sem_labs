function checkfieldsgive() {
    let name = document.getElementById('takename');
    let data = document.getElementById('takedata');
    document.getElementById('btn').disabled = name.value && data.value ? false : "disabled";
}
function checkfieldschange() {
    let name = document.getElementById('oldname'),
        auth = document.getElementById('oldauth'),
        data = document.getElementById('olddata');
    document.getElementById('save').disabled = name.value && auth.value && data.value ? false : "disabled";
}

function savechanges() {
    callAjaxPut(document.getElementById('oldname').value, document.getElementById('oldauth').value,  document.getElementById('olddata').value);
    alert("Changes saved!");
}


function callAjaxPut(name, author, data) {
    const xhttp = new XMLHttpRequest();
    xhttp.open("PUT", `/library/${document.location.href.split('/')[4]}`, true);
    xhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    xhttp.send(`author=${author}&name=${name}&created=${data}`);
}

function givebook() {
    callAjaxPost(true,document.getElementById("takename").value, document.getElementById("takedata").value);
    window.location=`/library/${document.location.href.split('/')[4]}`;
}
function returnbook() {
    callAjaxPost(false, "ok", getCurrentDate());
    window.location=`/library/${document.location.href.split('/')[4]}`;
}

function callAjaxPost(instock, takename, takedata) {
    const xhttp = new XMLHttpRequest();
    xhttp.open("POST", `/library/${document.location.href.split('/')[4]}`, true);
    xhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    xhttp.send(`stock=${instock}&date_returned=${takedata}&name_returned=${takename}`);
}

function getCurrentDate() {
    let date = new Date();
    let day = date.getDate();
    if (day.toString().length === 1) day = '0' + day;
    let month = date.getMonth()+1;
    if (month.toString().length === 1) month = '0' + month;

    return day + '.' + month + '.' + date.getFullYear();
}