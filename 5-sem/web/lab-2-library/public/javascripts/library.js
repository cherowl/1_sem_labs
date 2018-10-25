function checkfields() {
    let name = document.getElementById('addname'), auth = document.getElementById('addauth'), year = document.getElementById('adddatarel');
    document.getElementById('btn').disabled = name.value
    && auth.value && year.value ? false : "disabled";
}

function addbook() {
    callAjaxPut(document.getElementById("addname").value,
        document.getElementById("addauth").value,
        document.getElementById("adddatarel").value);
    document.getElementById('addbookform').style.display='none';
}

function callAjaxPut(author, name, created) {
    const xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            document.documentElement.innerHTML = this.responseText;
        }
    };
    xhttp.open("PUT", '/library', true);
    xhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    xhttp.send(`author=${author}&name=${name}&created=${created}`);
}

function deletebook(ind) {
    callAjaxDelete(ind);
}

function callAjaxDelete(ind) {
    const xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            document.documentElement.innerHTML = this.responseText;
        }
    };
    xhttp.open("DELETE", `/library/${ind}`, true);
    xhttp.send();
}

function filter_stock() {
    var table = document.getElementById('tablebooks');
    document.getElementById("filt_lost").disabled = !document.getElementById("filt_lost").disabled;
    for (var i = 1; i < table.rows.length; i++) {
        if(document.getElementById("filt_stock").checked) {
            if (table.rows[i].cells[5].innerHTML == "true") {
                table.rows[i].style.display = "";
            } else {
                table.rows[i].style.display = "none";
            }
        }
        else {
            table.rows[i].style.display = "";
        }
    }
}

function filter_lost(){
    var table = document.getElementById('tablebooks');
    document.getElementById("filt_stock").disabled = !document.getElementById("filt_stock").disabled;
    for (var i = 1; i < table.rows.length; i++) {
        if(document.getElementById("filt_lost").checked) {
            if((Number(Date.parse(table.rows[i].cells[6].innerHTML)) < Number(Date.parse(Date()))) && table.rows[i].cells[5].innerHTML == "false"){
                table.rows[i].style.display = "";
            } else {
                table.rows[i].style.display = "none";
            }
        }
        else {
            table.rows[i].style.display = "";
        }
    }
}