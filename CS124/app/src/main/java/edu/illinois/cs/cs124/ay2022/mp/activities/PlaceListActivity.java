package edu.illinois.cs.cs124.ay2022.mp.activities;

import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import androidx.appcompat.app.AppCompatActivity;
import com.opencsv.CSVReader;
import com.opencsv.CSVReaderBuilder;
import edu.illinois.cs.cs124.ay2022.mp.R;
import edu.illinois.cs.cs124.ay2022.mp.models.Place;
import edu.illinois.cs.cs124.ay2022.mp.network.Server;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class PlaceListActivity extends AppCompatActivity {

  private ListView listView;

  @Override
  protected void onCreate(final Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_place_list2);

    listView = findViewById(R.id.listView);

    String input =
        new Scanner(Server.class.getResourceAsStream("/places.csv"), "UTF-8")
            .useDelimiter("\\A")
            .next();
    CSVReader csvReader = new CSVReaderBuilder(new StringReader(input)).withSkipLines(2).build();

    List<String> places = new ArrayList<>();
    for (String[] parts : csvReader) {
      places.add(
          new Place(
                  parts[0],
                  parts[1],
                  Double.parseDouble(parts[2]),
                  Double.parseDouble(parts[3]),
                  parts[4])
              .getDescription());
    }

    ArrayAdapter arrayAdapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, places);
    listView.setAdapter(arrayAdapter);
  }
}
