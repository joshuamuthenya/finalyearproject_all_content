// 🔹 Replace with your Firebase config
const firebaseConfig = {
    apiKey: "YOUR_API_KEY",
    authDomain: "YOUR_PROJECT.firebaseapp.com",
    databaseURL: "https://YOUR_PROJECT.firebaseio.com",
    projectId: "YOUR_PROJECT_ID",
    storageBucket: "YOUR_PROJECT.appspot.com",
    messagingSenderId: "SENDER_ID",
    appId: "APP_ID"
};

// Initialize Firebase
firebase.initializeApp(firebaseConfig);
const dbRef = firebase.database().ref("/air_quality/predictions");

// Chart setup
const ctx = document.getElementById('sensorChart').getContext('2d');
const sensorChart = new Chart(ctx, {
    type: 'line',
    data: {
        labels: [], // timestamps
        datasets: [
            { label: 'Temperature (°C)', data: [], borderColor: 'red', fill: false },
            { label: 'Humidity (%)', data: [], borderColor: 'blue', fill: false },
            { label: 'CO (ppm)', data: [], borderColor: 'green', fill: false },
            { label: 'H2 (ppm)', data: [], borderColor: 'purple', fill: false },
            { label: 'LPG (ppm)', data: [], borderColor: 'orange', fill: false },
            { label: 'PM2.5', data: [], borderColor: 'brown', fill: false },
            { label: 'PM10', data: [], borderColor: 'gray', fill: false }
        ]
    },
    options: {
        responsive: true,
        plugins: {
            legend: { position: 'top' },
            title: { display: true, text: 'Live Sensor Readings' }
        },
        scales: {
            y: { beginAtZero: true }
        }
    }
});

// Listen for real-time updates
dbRef.limitToLast(50).on('child_added', snapshot => {
    const data = snapshot.val();
    const timestamp = snapshot.key;
    
    // Update AQ Level display
    document.getElementById('aq-level').innerText = data.AQ_Level || 'Unknown';

    // Update chart
    sensorChart.data.labels.push(timestamp);
    sensorChart.data.datasets[0].data.push(data.temperature);
    sensorChart.data.datasets[1].data.push(data.humidity);
    sensorChart.data.datasets[2].data.push(data.CO);
    sensorChart.data.datasets[3].data.push(data.hydrogen);
    sensorChart.data.datasets[4].data.push(data.LPG);
    sensorChart.data.datasets[5].data.push(data.PM2_5);
    sensorChart.data.datasets[6].data.push(data.PM10);

    // Keep chart limited to last 50 points
    if(sensorChart.data.labels.length > 50){
        sensorChart.data.labels.shift();
        sensorChart.data.datasets.forEach(ds => ds.data.shift());
    }

    sensorChart.update();
});
