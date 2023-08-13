package edu.illinois.cs.cs124.ay2022.mp.activities;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import edu.illinois.cs.cs124.ay2022.mp.R;
import edu.illinois.cs.cs124.ay2022.mp.application.FavoritePlacesApplication;
import edu.illinois.cs.cs124.ay2022.mp.models.Place;
import edu.illinois.cs.cs124.ay2022.mp.models.ResultMightThrow;
import java.util.concurrent.CompletableFuture;

public class AddPlaceActivity extends AppCompatActivity {
  @Override
  protected void onCreate(@Nullable final Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    setContentView(R.layout.activity_addplace);

    Intent backToMap = new Intent(this, MainActivity.class);
    backToMap.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK | Intent.FLAG_ACTIVITY_NEW_TASK);

    Button cancelButton = findViewById(R.id.cancel_button);
    cancelButton.setOnClickListener(
        v -> {
          startActivity(backToMap);
        });

    Button saveButton = findViewById(R.id.save_button);
    saveButton.setOnClickListener(
        v -> {
          TextView description = findViewById(R.id.description);
          Double latitude = Double.parseDouble(getIntent().getStringExtra("latitude"));
          Double longitude = Double.parseDouble(getIntent().getStringExtra("longitude"));

          Place place =
              new Place(
                  "d156abb1-7139-4406-afeb-b52e8ea6eb60",
                  "Whatever",
                  latitude,
                  longitude,
                  description.getText().toString());
          FavoritePlacesApplication favoritePlacesApp =
              (FavoritePlacesApplication) getApplication();
          CompletableFuture<ResultMightThrow<Boolean>> completableFuture =
              new CompletableFuture<>();
          favoritePlacesApp.getClient().postFavoritePlace(place, completableFuture::complete);
          startActivity(backToMap);
        });
  }
}
