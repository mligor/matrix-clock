import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { WifiConfigComponent } from './wifi-config/wifi-config.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { MatrixClockNavComponent } from './matrix-clock-nav/matrix-clock-nav.component';
import { LayoutModule } from '@angular/cdk/layout';
import {
	MatToolbarModule, MatButtonModule, MatSidenavModule, MatIconModule, MatListModule, MatTableModule,
	MatPaginatorModule, MatSortModule, MatGridListModule, MatCardModule, MatMenuModule,
	MatFormFieldModule, MatOptionModule, MatSelectModule, MatInputModule, MatProgressSpinnerModule
} from '@angular/material';
import { MatrixClockDashboardComponent } from './matrix-clock-dashboard/matrix-clock-dashboard.component';
import { HttpClientModule } from '@angular/common/http';
import { FormsModule } from '@angular/forms';

@NgModule({
	declarations: [
		AppComponent,
		WifiConfigComponent,
		MatrixClockNavComponent,
		MatrixClockDashboardComponent
	],
	imports: [
		BrowserModule,
		AppRoutingModule,
		BrowserAnimationsModule,
		LayoutModule,
		MatToolbarModule,
		MatButtonModule,
		MatSidenavModule,
		MatIconModule,
		MatListModule,
		MatTableModule,
		MatPaginatorModule,
		MatSortModule,
		MatGridListModule,
		MatCardModule,
		MatMenuModule,
		MatFormFieldModule,
		MatOptionModule,
		MatSelectModule,
		MatInputModule,
		MatProgressSpinnerModule,
		HttpClientModule,
		FormsModule
	],
	providers: [],
	bootstrap: [AppComponent]
})
export class AppModule { }
