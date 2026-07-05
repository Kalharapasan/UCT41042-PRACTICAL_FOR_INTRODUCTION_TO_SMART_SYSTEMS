class StreetLightLog {
  final int id;
  final int intensity;
  final String status;
  final String ledState;
  final DateTime createdAt;

  StreetLightLog({
    required this.id,
    required this.intensity,
    required this.status,
    required this.ledState,
    required this.createdAt,
  });

  factory StreetLightLog.fromJson(Map<String, dynamic> json) {
    return StreetLightLog(
      id: json['id'] as int,
      intensity: json['intensity'] as int,
      status: json['status'] ?? 'UNKNOWN',
      ledState: json['ledState'] ?? 'UNKNOWN',
      createdAt: json['created_at'] != null
          ? DateTime.parse(json['created_at']).toLocal()
          : DateTime.now(),
    );
  }

  /// Returns color representing the current LED state.
  /// GREEN  → bright ambient light, street light OFF
  /// BLUE   → dim ambient light, street light OFF
  /// RED    → dark, street light ON steady
  /// RED_BLINK → very dark, street light ON blinking
  LedColor get ledColor {
    switch (ledState.toUpperCase()) {
      case 'GREEN':
        return LedColor.green;
      case 'BLUE':
        return LedColor.blue;
      case 'RED':
        return LedColor.red;
      case 'RED_BLINK':
        return LedColor.redBlink;
      default:
        return LedColor.unknown;
    }
  }

  String get conditionLabel {
    switch (ledState.toUpperCase()) {
      case 'GREEN':
        return 'Bright — Light OFF';
      case 'BLUE':
        return 'Dim — Light OFF';
      case 'RED':
        return 'Dark — Light ON';
      case 'RED_BLINK':
        return 'Very Dark — Light ON (Blinking)';
      default:
        return 'Unknown Condition';
    }
  }
}

enum LedColor { green, blue, red, redBlink, unknown }
