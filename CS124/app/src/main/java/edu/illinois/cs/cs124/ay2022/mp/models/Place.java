package edu.illinois.cs.cs124.ay2022.mp.models;

import java.util.ArrayList;
import java.util.List;

/*
 * Model storing information about a place retrieved from the backend server.
 *
 * You will need to understand some of the code in this file and make changes starting with MP1.
 */
@SuppressWarnings("unused")
public final class Place {
  /*
   * The Jackson JSON serialization library that we are using requires an empty constructor.
   * So don't remove this!
   */
  public Place() {}

  public Place(
      final String setId,
      final String setName,
      final double setLatitude,
      final double setLongitude,
      final String setDescription) {
    id = setId;
    name = setName;
    latitude = setLatitude;
    longitude = setLongitude;
    description = setDescription;
  }

  // ID of the place
  private String id;

  public String getId() {
    return id;
  }

  // Name of the person who submitted this favorite place
  private String name;

  public String getName() {
    return name;
  }

  // Latitude and longitude of the place
  private double latitude = 200.0;

  public double getLatitude() {
    return latitude;
  }

  private double longitude = 200.0;

  public double getLongitude() {
    return longitude;
  }

  // Description of the place
  private String description;

  public String getDescription() {
    return description;
  }

  public static List<Place> search(final List<Place> object, final String search) {
    if (object == null || search == null) {
      throw new IllegalArgumentException();
    }

    if (object.isEmpty() || search.trim().equals("")) {
      return object;
    }

    List<Place> p1 = new ArrayList<>();
    String newSearch = search.trim().toLowerCase();

    for (Place x : object) {
      StringBuilder des = new StringBuilder(x.getDescription());
      for (int i = 0; i < des.length(); i++) {
        if (des.charAt(i) == '.'
            || des.charAt(i) == '!'
            || des.charAt(i) == '?'
            || des.charAt(i) == ','
            || des.charAt(i) == ':'
            || des.charAt(i) == ';'
            || des.charAt(i) == '/') {
          des.setCharAt(i, ' ');
        }
      }

      for (int i = 0; i < des.length(); i++) {
        if (!(Character.isAlphabetic(des.charAt(i))
            || Character.isDigit(des.charAt(i))
            || des.charAt(i) == ' ')) {
          des.deleteCharAt(i);
        }
      }
      String des2 = des.toString();
      String[] arr = des2.split(" ");
      for (String y : arr) {
        if (y.toLowerCase().equals(newSearch)) {
          p1.add(x);
          break;
        }
      }
    }

    return p1;
  }
}
