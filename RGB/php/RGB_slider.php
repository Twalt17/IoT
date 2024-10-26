<html>
    <head></head>
    <body>
        <h1 style="color:green;">IoT Course</h1>
        
        <form method="post" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']); ?>">
            Click to turn ON LED_1: <input type="submit" name="fname" value="on">
            <p></p>
            Click to turn OFF LED_1: <input type="submit" name="fname" value="off">
        </form>
        
        <form method="post" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']);?>">
            <label for="slider1">Slider 1 (0-255): </label>
            <input type= "range" id="slider1" name="slider1" min="0" max="255" value="0" oninput="this.nextElemintSibling.value = this.value">
            <output>0</output>
            <p></p>
            
            <label for="slider2">Slider 2 (0-255): </label>
            <input type= "range" id="slider2" name="slider2" min="0" max="255" value="0" oninput="this.nextElemintSibling.value = this.value">
            <output>0</output>
            <p></p>
            
            <label for="slider3">Slider 3 (0-255): </label>
            <input type= "range" id="slider3" name="slider3" min="0" max="255" value="0" oninput="this.nextElemintSibling.value = this.value">
            <output>0</output>
            <p></p>
            
            <input type="hidden" name="ledState" value="<?php echo isset($_POST['fname']) ? $_POST['fname'] : ''; ?>">
            
            <input type="submit" value = "Submit Values">
        </form>
        
        <?php
        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            if (file_exists("results.txt")) {
        $lastData = file_get_contents("results.txt");
        if ($lastData !== false) {
            $data = json_decode($lastData, true);
            $ledState = isset($data['Node1_LED1']) ? $data['Node1_LED1'] : 'off'; // Get the LED state
        }
    }

    
    
            $var1 = isset($_POST["fname"]) ? $_POST["fname"] : $_POST["ledState"];

            // Create an array to hold the data for LED_1 and Node
            $data = array(
                "Node1_LED1" => $var1 === "on" ? "on" : ($var1 === "on" ? "on" : ($var1 === "off" ? "off" : $ledState))
                
            );

            // Convert the array to JSON format
            $json_data = json_encode($data);

            // Write to file
            $myfile = fopen("results.txt", "w") or die("Unable to open file!");
            fwrite($myfile, $json_data);
            fclose($myfile);

            // print confirmation
            echo "<p>Data saved: " . htmlspecialchars($json_data) . "</p>";
            
        if (file_exists("sliders.txt")) {
        $last_slider_data = file_get_contents("sliders.txt");
        if ($last_slider_data !== false) {
            $datas = json_decode($last_slider_data, true);
            $slider1_state = isset($datas['Node1_RGB1']) ? $datas['Node1_RGB1'] : 'off'; // Get the LED state
            $slider2_state = isset($datas['Node1_RGB2']) ? $datas['Node1_RGB2'] : 'off'; // Get the LED state
            $slider3_state = isset($datas['Node1_RGB3']) ? $datas['Node1_RGB3'] : 'off'; // Get the LED state
        }
    }
            
        // Update the slider value based on the slider submission
        $slider1_value = isset($_POST["slider1"]) ? $_POST["slider1"] : $slider1_state;
        $slider2_value = isset($_POST["slider2"]) ? $_POST["slider2"] : $slider2_state;
        $slider3_value = isset($_POST["slider3"]) ? $_POST["slider3"] : $slider3_state;


        // Create a JSON array for the slider state
        $slider_data = array(
            "Node1_RGB1" => $slider1_value,
            "Node1_RGB2" => $slider2_value,
            "Node1_RGB3" => $slider3_value
            
        );

        // Save the slider state to sliders.txt in JSON format
        file_put_contents("sliders.txt", json_encode($slider_data));

        // Print the slider value
        echo "Slider one value: " . htmlspecialchars($slider1_value) . "<br>";
        echo "Slider two value: " . htmlspecialchars($slider2_value) . "<br>";
        echo "Slider three value: " . htmlspecialchars($slider3_value) . "<br>";
    }
    ?>
</body>
</html>