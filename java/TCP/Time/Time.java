package Time;

import java.util.Calendar;

public class Time {
    private Time() {}

    private static Calendar calendar = Calendar.getInstance();

    public static String getDayTime() {
        int year = calendar.get(Calendar.YEAR);
        int month = calendar.get(Calendar.MONTH);
        int day = calendar.get(Calendar.DAY_OF_MONTH);

        return String.format("%d-%02d-%02d", year, month, day);
    }

    public static String getSecondTime() {
        int hour = calendar.get(Calendar.HOUR_OF_DAY);
        int minute = calendar.get(Calendar.MINUTE);
        int second = calendar.get(Calendar.SECOND);
        return String.format("%02d:%02d:%02d", hour, minute, second);
    }
    public static void main(String[] args) {
        System.out.println(getDayTime());
        System.out.println(getSecondTime());
    }
}
